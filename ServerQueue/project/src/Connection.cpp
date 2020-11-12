//
// Created by lerakry on 12.11.2020.
//

#include "Connection.h"

tcp_server::Connection::Connection(std::string ip, const uint16_t port) {}
tcp_server::Connection::Connection(Socket& socket) {}
size_t tcp_server::Connection::write(const std::string& data) {
    return 5;
}
size_t tcp_server::Connection::read(std::string& data) {
    return 20;
}
void tcp_server::Connection::close() {}
void tcp_server::Connection::set_timeout(int time) {}
bool tcp_server::Connection::is_opened() {}
void tcp_server::Connection::connect(std::string& addr, uint16_t port) {}
int tcp_server::Connection::get_connection() {
    return 1;
}
