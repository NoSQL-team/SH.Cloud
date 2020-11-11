//
// Created by Andrew Kireev on 02.11.2020.
//

#ifndef NOSKOOL_CONNECTION_H
#define NOSKOOL_CONNECTION_H

#include <string>
#include "utilty.h"


namespace tcp_network {

    class Connection {
    public:
        friend class IServer;

        Connection(const std::string& ip, const uint16_t port);

        explicit Connection(Socket& fd);

        explicit Connection(Socket&& fd);

        virtual ~Connection() noexcept;

        size_t write(const std::string& message);

        size_t read(const std::string& message);

        void close();

        [[nodiscard]] bool is_opened() const;

        void set_timeout(int time);

        void connect(const std::string& addr, uint16_t port);

        void send_size(const size_t size);

        size_t recv_size();

        void set_serv_name(const std::string& serv_name);

        std::string get_serv_name() const;

        int get_connnection() const;

    private:

        Socket sock_fd_;
        bool is_readable_ = false;
        std::string server_name_;
    };

}

#endif //NOSKOOL_CONNECTION_H
