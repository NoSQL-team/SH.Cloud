//
// Created by amartery on 08.11.2020.
//

#include <server_posts_interface.h>
#include "server_posts.h"


namespace tcp_server {

    TCPServer::TCPServer(const std::string& ip, uint16_t port) {}

    TCPServer::~TCPServer() noexcept{}

    void TCPServer::close() {}

    Connection TCPServer::accept() {
        return Connection();
    }

    void TCPServer::open(const std::string& ip, uint16_t port) { }

    void TCPServer::set_max_connection(int num_connections);

    ServerPosts::ServerPosts(const std::string& ip, uint16_t port);
    ServerPosts::~ServerPosts() noexcept = default;



    // void ServerPosts::add_friend(std::map<std::string, std::string>& request) {}

    void ServerPosts::find_posts_for_user(int id) {}

    void ServerPosts::all_posts() {}

    void ServerPosts::find_user_posts(int id) {}

    void ServerPosts::create_post(int id, Post& post) {}

    void ServerPosts::change_post(int id, int post_id, Post& post_updates) {}

    void ServerPosts::delete_post(int id, int post_id) {}

    Post& ServerPosts::get_one_post(int post_id) {
        Post test = {0, 0, nullptr, nullptr, nullptr, 0};
        return test;
    }
}