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



    class IServer {
    public:
        IServer(const std::string& ip, uint16_t port);

        virtual ~IServer() noexcept;

        virtual void close();

        virtual Connection accept();

        virtual void open(const std::string& ip, int port);

        virtual void create_epoll();

        virtual void add_epoll(int fd,  uint32_t events);

        virtual void event_loop();

        virtual void accept_clients();

        virtual void handle_client(int fd, uint32_t event);

        virtual void close_epoll();

        virtual void erase_connection(const Connection& con);

        virtual void modify_epoll(int fd, uint32_t events);

    private:
        Socket listenfd_;
        Socket epoll_;
        std::unordered_map<int, Connection> сonnections_;
    };

}

#endif //NOSKOOL_UTILTY_H
