//
// Created by steve on 04.12.2020.
//

#include "../include/server.h"

// id_request /posts/fuser/?user_id=%                   - Запрос постов для конкретного пользователя
// id_request /posts/all/                               - Запрос всех постов
// id_request /posts/user/?user_id=%                    - Запрос постов конкретного пользователя
// id_request /posts/post/?post_id=%                    - Запрос определённого поста из БД
// id_request /posts/dlt/?post_id=%&user_id=%           - Запрос на удаление post_id поста пользователем id (второй параметр)
// id_request /posts/create/?user_id=% {body}           - Запрос на создание поста пользователем id
// id_request /posts/upd/?user_id=%&post_id=% {body}    - Запрос на изменение поста post_id пользователем id (второй параметр)



int main() {

    io::io_context io_context;
    TCPServer server(io_context, 2347);  // boost::lexical_cast<std::uint16_t>(argv[1])
    server.add_endpoint();
    io_context.run();

    return 0;
}


