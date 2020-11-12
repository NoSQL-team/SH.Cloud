//
// Created by lerakry on 12.11.2020.
//

#ifndef SERVERQUEUE_SSERVER_H
#define SERVERQUEUE_SSERVER_H

#include <unordered_map>

#include "Connection.h"

namespace tcp_server {

    class SServer {
    public:
        SServer() = default;

        SServer(const std::string& ip, const uint16_t port);

        ~SServer() noexcept;

        void open(const std::string &ip, uint16_t port);

        void close() noexcept;

        Connection accept();

        void client(Socket& socket, uint16_t port);

        void erase_connection(Connection &connection);

    protected:
        Socket socket_;
        std::unordered_map<int, Connection> connections;
    };
}

#endif //SERVERQUEUE_SSERVER_H
