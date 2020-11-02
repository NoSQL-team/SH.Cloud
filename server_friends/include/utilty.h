//
// Created by Andrew Kireev on 02.11.2020.
//

#ifndef NOSKOOL_UTILTY_H
#define NOSKOOL_UTILTY_H

namespace tcp_network {

    class Socket {
    public:
        explicit Socket(const int fd) noexcept;

        Socket() = default;

        explicit Socket(Descriptor&& other) noexcept;

        ~Socket() noexcept;

        Socket& operator=(const int fd);

        void close() noexcept;

    private:
        int socket_ = -1;
    };

    template <class T>
    struct Request
    {
        // номер сервера приложения
        unsigned servie_number:8;
        // приоритетность запроса
        unsigned priority:1;
        // тип запроса
        unsigned req_type:3;
        // тело, в зависимости от сервера назначения меняется
        T req_body;
    };

    template <class T>
    struct Response
    {
        // тело, в зависимости от сервера назначения меняется
        T resp_body;
    };

}

#endif //NOSKOOL_UTILTY_H
