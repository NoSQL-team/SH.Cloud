//
// Created by steve on 15.12.2020.
//

#include "../include/server.h"


void TCPServer::add_endpoint() {
    dispatcher.emplace(
            "/api/posts/all/",
            dispatcher_entry{
                    0,
                    false,
                    [this](
                            const std::string& id_request,
                            const std::map<std::string, size_t>& args
                    ) -> std::string{
                        return hand.all_posts(id_request, args);
                    }
            }
    );
    dispatcher.emplace(
            "/api/posts/fuser/",
            dispatcher_entry{
                    1,
                    false,
                    [this](
                            const std::string& id_request,
                            const std::map<std::string, size_t>& args
                    ) -> std::string{
                        return hand.for_user(id_request, args);
                    }
            });

    dispatcher.emplace(
            "/api/posts/user/",
            dispatcher_entry{
                    1,
                    false,
                    [this](
                            const std::string& id_request,
                            const std::map<std::string, size_t>& args
                    ) -> std::string {
                        return hand.user_posts(id_request, args);
                    }
            });
    dispatcher.emplace(
            "/api/posts/post/",
            dispatcher_entry{
                    1,
                    false,
                    [this](
                            const std::string& id_request,
                            const std::map<std::string,size_t>& args
                    )-> std::string {
                        return hand.one_post(id_request, args);
                    }
            });
    dispatcher.emplace(
            "/api/posts/dlt/",
            dispatcher_entry{
                    2,
                    true,
                    [this](
                            const std::string& id_request,
                            const std::map<std::string, size_t>& args
                    ) -> std::string {
                        return hand.delete_post(id_request, args);
                    }
            });
    dispatcher.emplace(
            "/api/posts/like/add/",
            dispatcher_entry{
                    2,
                    true,
                    [this](
                            const std::string& id_request,
                            const std::map<std::string, size_t>& args
                    ) -> std::string {
                        return hand.add_like(id_request, args);
                    }
            });
    dispatcher.emplace(
            "/api/posts/like/del/",
            dispatcher_entry{
                    2,
                    true,
                    [this](
                            const std::string& id_request,
                            const std::map<std::string, size_t>& args
                    ) -> std::string {
                        return hand.del_like(id_request, args);
                    }
            });

    // ендпоинты требующие боди
    dispatcher_with_body.emplace(
            "/api/posts/create/",
            dispatcher_entry_with_body{
                    1,
                    true,
                    [this](std::string const& id_request,
                           std::map<std::string, size_t> const& args,
                           std::string& body) -> std::string {
                        return hand.create_post(id_request, args, body);
                    }
            });

}


void TCPServer::accept() {
    acceptor.async_accept(socket, [&] (error_code error) {
        std::make_shared<Session>(std::move(socket), dispatcher, dispatcher_with_body)->Session::start();
        accept();
    });
}
