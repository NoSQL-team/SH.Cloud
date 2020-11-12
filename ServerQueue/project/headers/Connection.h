//
// Created by lerakry on 12.11.2020.
//

#ifndef SERVERQUEUE_CONNECTION_H
#define SERVERQUEUE_CONNECTION_H

#include <iostream>
#include <string>

#include "Socket.h"

namespace tcp_server {

    class Connection {
    public:
        Connection() = default;

        Connection(std::string ip, const uint16_t port);

        Connection(const Connection& con) = default;

        Connection(Connection&& con) = default;

        Connection(Socket& socket);

        ~Connection() = default;


        size_t write(const std::string &data);

        size_t read(std::string &data);

        void close();

        void set_timeout(int time);

        bool is_opened();

        void connect(std::string &addr, uint16_t port);

        int get_connection();

    private:
        Socket socket_;
    };
}

#endif //SERVERQUEUE_CONNECTION_H
