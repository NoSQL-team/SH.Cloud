//
// Created by lerakry on 12.11.2020.
//

#ifndef SERVERUSERS_CONNECTION_H
#define SERVERUSERS_CONNECTION_H

#include <iostream>
#include <string>

#include "Socket.h"

namespace tcp_server {
    class Connection {
    public:
        Connection(std::string ip, const uint16_t port);
        Connection() = default;
        Connection(const Connection& con) = default;
        Connection(Connection&& con) = default;
        Connection(Socket& socket);
        ~Connection();
        size_t write(const std::string& data);
        size_t read(std::string& data);
        void close();
        void set_timeout(int time);
        bool is_opened();
        void connect(std::string& addr, uint16_t port);
        int get_connection();
    private:
        Socket socket_;
    };
}

#endif //SERVERUSERS_CONNECTION_H
