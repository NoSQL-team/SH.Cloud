//
// Created by Andrew Kireev on 12.11.2020.
//

#include "server_interface.h"


namespace tcp_network {

    IServer::IServer(const std::string &ip, uint16_t port) {}

    IServer::~IServer() noexcept {}

    void IServer::close() {}

    Connection IServer::accept() {
        return Connection();
    }

    void IServer::open(const std::string &ip, uint16_t port) {}

    void IServer::create_epoll() {}

    void IServer::add_epoll(Socket &fd, uint32_t events) {}

    void IServer::event_loop() {}

    void IServer::accept_clients() {}

    void IServer::handle_client(Socket &fd, uint32_t event) {}

    void IServer::close_epoll() {}

    void IServer::erase_connection(const Connection &con) {}

    void IServer::modify_epoll(Socket &fd, uint32_t events) {}
}