//
// Created by lerakry on 12.11.2020.
//

#include "Socket.h"

tcp_server::Socket::Socket(const int fd) {}
tcp_server::Socket::~Socket() {}
tcp_server::Socket::Socket(Socket&& other) noexcept {}
tcp_server::Socket& tcp_server::Socket::operator=(const int fd) {}
void tcp_server::Socket::close() noexcept {}
int tcp_server::Socket::get_socket() {
    return 9;
}

