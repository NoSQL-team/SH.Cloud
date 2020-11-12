//
// Created by amartery on 08.11.2020.
//

#ifndef TESTS_SERVER_POSTS_INTERFACE_H
#define TESTS_SERVER_POSTS_INTERFACE_H

#include "connection.h"
#include "utility.h"


namespace tcp_server {
    class TCPServer {
    public:
        TCPServer() = default;
        TCPServer(const std::string& ip, uint16_t port);
        virtual ~TCPServer() noexcept;
        virtual void close();
        virtual Connection accept();
        virtual void open(const std::string& ip, uint16_t port);
        virtual void set_max_connection(int num_connections);

    protected:
        tcp_server::Socket listenfd_;
        size_t max_connection_ = 1;
        JsonParser parser_;
    };

}

#endif  // TESTS_SERVER_POSTS_INTERFACE_H