#include "../include/types.h"
#include "../include/utility_parser.h"



class Session : public std::enable_shared_from_this<Session> {
public:

    Session(tcp::socket&& socket,
            dispatcher_type const& dispatcher,
            dispatcher_type_with_body const& dispatcher_with_body)
    : socket    (std::move(socket))
    , dispatcher(dispatcher)
    , dispatcher_with_body(dispatcher_with_body) {}

    void start() {
        write("POSTS server is ready to serve");
        write();
        read();
    }

private:

    void write(std::string const& string) {
        outgoing.push(string + "\r\n> ");
    }


    void read() {
        io::async_read_until(
                socket,
                incoming,
                "\n",
                std::bind(&Session::on_read, shared_from_this(), std::placeholders::_1,  std::placeholders::_2));
    }


    void on_read(error_code error, std::size_t bytes_transferred) {
        if(!error) {
            std::istream stream(&incoming);
            std::string line;
            std::getline(stream, line);
            incoming.consume(bytes_transferred);
            boost::algorithm::trim(line);
            if(!line.empty()) {
                dispatch(line);
            }
            read();
        }
    }

// TODO: реализовать функцию отправки на сокет http сервера

    void write() {
        io::async_write(
                socket,
                io::buffer(outgoing.front()),
                std::bind(&Session::on_write, shared_from_this(), std::placeholders::_1,  std::placeholders::_2));
    }


    void on_write(error_code error, std::size_t bytes_transferred) {
        if(!error) {
            outgoing.pop();
            if(!outgoing.empty()) {
                write();
            }
        }
    }


// Находим соответствующий обработчик команд, применяем его,
// если он найден, отправляем ответ обратно.
    void dispatch(std::string const& line) {
        std::stringstream response; // строка ответа
        auto parameters_request = split(line, " ");

        if (parameters_request.size() == 2) { // боди нет
            try {
                RequestWithoutBody result = parse_without_body(parameters_request);
                if(auto it = dispatcher.find(result.command); it != dispatcher.cend()) {  // поиск хендлера
                    auto const& entry = it->second;
                    if(entry.args == result.args.size()) {
                        try {
                            response << entry.handler(result.id_request, result.args);  // вызов хендлера
                        } catch(std::exception const& e) {
                            response << "404";
                        }
                    } else {
                        response << "404";
                    }
                } else {
                    response << "404";
                }
            } catch(boost::bad_lexical_cast &) {
                response << "404";
            }

        } else if (parameters_request.size() == 3) {  // боди есть
            try {
                RequestWithBody result = parse_with_body(parameters_request);
                if(auto it = dispatcher_with_body.find(result.command); it != dispatcher_with_body.cend()) {  // поиск хендлера
                    auto const& entry = it->second;
                    if(entry.args == result.args.size()) {
                        try {
                            response << entry.handler(result.id_request, result.args, result.body);  // вызов хендлера
                        } catch(std::exception const& e) {
                            response << "404";
                        }
                    } else {
                        response << "404";
                    }
                } else {
                    response << "404";
                }
            } catch(boost::bad_lexical_cast &) {
                response << "404";
            }
        } else {
            response << "404";
        }

        // Поместим ответ в исходящую очередь
        write(response.str());

        // Если очередь была пуста до этого, то мы должны инициировать доставку сообщения обратно клиенту
        if(outgoing.size() == 1) {
            write();
        }
    }

// Сеанс считывает входящие данные с помощью async_read_until до тех пор,
// пока не будет найден символ \n, а затем анализирует полученную строку.

    // TODO: добавить еще сокет для отправки на сразу на http сервер
    tcp::socket socket;
    // сохраняем диспетчер внутри объекта сервера и передаем ссылку на него в сеанс
    dispatcher_type const& dispatcher;
    dispatcher_type_with_body const& dispatcher_with_body;
    io::streambuf incoming;
    std::queue<std::string> outgoing;
};




