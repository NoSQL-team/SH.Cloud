//
// Created by steve on 04.12.2020.
//

#ifndef POSTS_SERVER_H
#define POSTS_SERVER_H

// как работает сервер
// 1 Принимаем входящее соединение на заданном порту
// 2 Создаем объект сеанса для принятого соединения
// 3 Переходим к шагу 1

// как работают сессии
// 1 Считываем строку до тех пор, пока не будет найден символ \n
// 2 Парсинг типа команды и ее аргументов
// 3 Вызываем обработчик ответственный за эту команду, и формируем ответную строку
// 4 Отправляем ответ клиенту

#include "../include/session.h"
#include "../include/handlers.h"

class TCPServer {
public:

    TCPServer(io::io_context& io_context, std::uint16_t port)
            : io_context(io_context)
            , acceptor  (io_context, tcp::endpoint(tcp::v4(), port)) {

        accept();
    }


    void add_endpoint() {
        dispatcher.emplace("/posts/fuser/", dispatcher_entry{1, for_user});
        dispatcher.emplace("/posts/all/", dispatcher_entry{0, all_posts});
        dispatcher.emplace("/posts/user/", dispatcher_entry{1, user_posts});
        dispatcher.emplace("/posts/post/", dispatcher_entry{1, one_post});
        dispatcher.emplace("/posts/dlt/", dispatcher_entry{2, delete_post});
        // ендпоинты требующие боди
        dispatcher_with_body.emplace(
                                    "/posts/create/",
                                     dispatcher_entry_with_body{1, create_post}
                                     );
        dispatcher_with_body.emplace(
                                    "/posts/upd/",
                                    dispatcher_entry_with_body{2, update_post}
                                     );
    }

private:

    void accept() {
        socket.emplace(io_context);

        acceptor.async_accept(*socket, [&] (error_code error) {
            std::make_shared<Session>(std::move(*socket), dispatcher, dispatcher_with_body)->Session::start();
            accept();
        });
    }
    io::io_context& io_context;
    tcp::acceptor acceptor;
    std::optional<tcp::socket> socket;
    dispatcher_type dispatcher;  // map обработчиков команд описан в types.hpp
    dispatcher_type_with_body dispatcher_with_body;
};


#endif // POSTS_SERVER_H
