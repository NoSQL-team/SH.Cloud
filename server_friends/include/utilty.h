//
// Created by Andrew Kireev on 02.11.2020.
//

#ifndef NOSKOOL_UTILTY_H
#define NOSKOOL_UTILTY_H


namespace tcp_network {

    class Socket {
    public:
        explicit Socket(const int& fd) noexcept;

        Socket() = default;

        explicit Socket(Socket&& other) noexcept;

        ~Socket() noexcept;

        Socket& operator=(const int fd);

        void close() noexcept;

        int get() const;

    private:
        int socket_ = -1;
    };

}

#endif //NOSKOOL_UTILTY_H
