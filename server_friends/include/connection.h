//
// Created by Andrew Kireev on 02.11.2020.
//

#ifndef NOSKOOL_CONNECTION_H
#define NOSKOOL_CONNECTION_H

#include "utilty.h"

namespace tcp_network {

    class Connection {
    public:
        friend class Server;

        Connection(const std::string& ip, const uint16_t port);

        Connection(int fd);

        Connection(Descriptor&& fd);

        ~Connection() noexcept;

        template <typename Message>
        size_t write(Message& msg);

        template <typename Message>
        size_t read(Message& msg);

        void close();

        [[nodiscard]] bool is_opened() const;

        void set_timeout(int time);

        void connect(const std::string& addr, uint16_t port);

        void send_size(const size_t& data);

        void recv_size(size_t& data);

        std::string get_buffer() const;

        int get_con() const;

    private:

        Socket sock_fd_;
        bool is_readable = false;
    };

}

#endif //NOSKOOL_CONNECTION_H
