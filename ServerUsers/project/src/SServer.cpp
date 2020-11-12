//
// Created by lerakry on 12.11.2020.
//

#include "SServer.h"

tcp_server::SServer::SServer(const std::string& ip, const uint16_t port) {}
tcp_server::SServer::~SServer() noexcept {}
void tcp_server::SServer::open(const std::string& ip, uint16_t port) {}
void tcp_server::SServer::close() noexcept {}
tcp_server::Connection tcp_server::SServer::accept() {
    return Connection();
}
void tcp_server::SServer::client(Socket& socket, uint16_t port) {}
void tcp_server::SServer::erase_connection(Connection& connection) {}


