//
// Created by lerakry on 12.11.2020.
//

#ifndef SERVERQUEUE_SOCKET_H
#define SERVERQUEUE_SOCKET_H

namespace tcp_server {

    class Socket {
    public:
        explicit Socket(const int fd);

        Socket() = default;

        ~Socket();

        explicit Socket(Socket &&other) noexcept;

        Socket &operator=(const int fd);

        void close() noexcept;

        int get_socket();

    private:
        int fd = -1;
    };
}

#endif //SERVERQUEUE_SOCKET_H
