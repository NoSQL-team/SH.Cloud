//
// Created by Andrew Kireev on 12.11.2020.
//

#ifndef TESTS_SERVER_INTERFACE_H
#define TESTS_SERVER_INTERFACE_H

#include <string>
#include <map>
#include "connection.h"

namespace tcp_network {

    class IServer {
    public:
        IServer() = default;

        IServer(const std::string& ip, uint16_t port);

        virtual ~IServer() noexcept;

        virtual void close();

        virtual Connection accept();

        virtual void open(const std::string& ip, uint16_t port);

        virtual void create_epoll();

        virtual void add_epoll(Socket& fd,  uint32_t events);

        virtual void event_loop();

        virtual void accept_clients();

        virtual void handle_client(Socket& fd, uint32_t event);

        virtual void close_epoll();

        virtual void erase_connection(const Connection& con);

        virtual void modify_epoll(Socket& fd, uint32_t events);

    protected:
        Socket listenfd_;
        Socket epoll_;
        std::map<int, Connection> сonnections_;
        ParseJson parser_;
    };

}

#endif //TESTS_SERVER_INTERFACE_H
