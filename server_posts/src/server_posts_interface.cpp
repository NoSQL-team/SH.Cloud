//
// Created by steve on 12.11.2020.
//

#include "server_posts_interface.h"


namespace tcp_server {
    TCPServer::TCPServer(const std::string &ip, uint16_t port) {}
    TCPServer::~TCPServer() noexcept = default;
    void TCPServer::close() {}
    Connection TCPServer::accept() {
        return Connection();
    }
    void TCPServer::open(const std::string &ip, uint16_t port) {}
    void TCPServer::set_max_connection(int num_connections) {}
}