//
// Created by steve on 15.12.2020.
//

#include "../include/session.h"
#include "../include/utility_for_lib.h"


void Session::start() {
    write("POSTS server is ready to serve");
    write();
    read();
}


void Session::write(std::string const& string) {
    outgoing.push(string + "\r\n> ");
}


void Session::read() {
    io::async_read_until(
            socket,
            incoming,
            "\r",
            std::bind(&Session::on_read, shared_from_this(), std::placeholders::_1,  std::placeholders::_2));
}


void Session::on_read(error_code error, std::size_t bytes_transferred) {
    if(!error) {
        std::istream stream(&incoming);
        std::string line;
        std::string full_line = "";
        while(std::getline(stream, line)) {
            full_line += line + " ";
        }
        incoming.consume(bytes_transferred);
        std::string trim_full_line = reduce(full_line);
        if(!line.empty()) {
            dispatch(trim_full_line);
        }
        read();
    }
}

// TODO: реализовать функцию отправки на сокет http сервера

void Session::write() {
    io::async_write(
            socket,
            io::buffer(outgoing.front()),
            std::bind(&Session::on_write, shared_from_this(), std::placeholders::_1,  std::placeholders::_2));
}


void Session::on_write(error_code error, std::size_t bytes_transferred) {
    if(!error) {
        outgoing.pop();
        if(!outgoing.empty()) {
            write();
        }
    }
}


// Находим соответствующий обработчик команд, применяем его,
// если он найден, отправляем ответ обратно.
void Session::dispatch(std::string const& line) {
    std::stringstream response; // строка ответа

    auto parameters_request = split(line, " ");

    if (parameters_request.size() == 3) { // боди нет
        try {
            RequestWithoutBody result = parse_without_body(parameters_request);
            // поиск хендлера
            if(auto it = dispatcher.find(result.command); it != dispatcher.cend()) {
                auto const& entry = it->second;
                // проверяем количество параметров из url и авторизирован ли пользователь
                if(entry.args == result.args.size() && entry.required_auth == result.is_authorized) {
                    try {
                        // вызов хендлера
                        std::cout << entry.handler(result.id_request, result.args);
                    } catch(std::exception const& e) {
                        std::cout << "{'error': 'handler execution error'}";
                    }
                } else {
                    std::cout << "{'error': 'bad args or not authorized'}";
                }
            } else {
                std::cout << "{'error': 'handler not found'}";
            }
        } catch(boost::bad_lexical_cast &) {
            std::cout << "{'error': 'parse request error'}";
        }

    } else if (parameters_request.size() == 4) {  // боди есть
        try {
            RequestWithBody result = parse_with_body(parameters_request);
            // поиск хендлера
            if(auto it = dispatcher_with_body.find(result.command); it != dispatcher_with_body.cend()) {
                auto const& entry = it->second;
                // проверяем количество параметров из url и авторизирован ли пользователь
                if(entry.args == result.args.size() && entry.required_auth == result.is_authorized) {
                    try {
                        // вызов хендлера
                        std::cout << entry.handler(result.id_request, result.args, result.body);
                    } catch(std::exception const& e) {
                        std::cout << "{'error': 'handler execution error'}";
                    }
                } else {
                    std::cout << "{'error': 'bad args or not authorized'}";
                }
            } else {
                std::cout << "{'error': 'handler not found'}";
            }
        } catch(boost::bad_lexical_cast &) {
            std::cout << "{'error': 'parse request error'}";
        }
    } else {
        std::cout <<
                        "{'error': 'too many arguments (" +
                        std::to_string(parameters_request.size())
                        + ")'}";
    }

    response << "OK";
    // Поместим ответ в исходящую очередь
    write(response.str());

    // Если очередь была пуста до этого, то мы должны инициировать доставку сообщения обратно клиенту
    if(outgoing.size() == 1) {
        write();
    }
}

