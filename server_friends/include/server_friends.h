//
// Created by Andrew Kireev on 02.11.2020.
//

#ifndef NOSKOOL_SERVER_FRIENDS_H
#define NOSKOOL_SERVER_FRIENDS_H

#include "connection.h"

namespace tcp_network {

    class ServerFriends {
    public:
        ServerFriends(const std::string& ip, uint16_t port);

        ~ServerFriends() noexcept;

        void close();

        Connection accept();

        void open(const std::string& ip, int port);

        void create_epoll();

        void add_epoll(int fd,  uint32_t events);

        void event_loop();

        void accept_clients();

        void handle_client(int fd, uint32_t event);

        void close_epoll();

        void erase_connection(const Connection& con);

        void modify_epoll(int fd, uint32_t events);

    private:
        Socket listenfd_;
        Socket epoll_;
        std::unordered_map<int, Connection> connects_;
    };

}

#endif //NOSKOOL_SERVER_FRIENDS_H
