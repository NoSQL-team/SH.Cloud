//
// Created by Andrew Kireev on 11.11.2020.
//

#include "connection.h"
#include <unistd.h>


namespace tcp_network {

    template <typename... Args>
    Connection::Connection(Args&&...) {}

    Connection::~Connection() {}

    Connection::Connection(Socket&& fd) {}

    Connection::Connection(Connection&& con) noexcept {}

    Connection::Connection(std::string& ip, uint16_t port) {}

    size_t Connection::write(const std::string& message) {
        return size_t(0);
    }

    size_t Connection::read(const std::string& message) {
        return size_t(0);
    }

    void Connection::close() {}

    bool Connection::is_opened() const {
        return true;
    }

    void Connection::set_timeout(int time) {}

    void Connection::connect(const std::string& addr, uint16_t port) {}

    void Connection::send_size(const size_t size) {}

    size_t Connection::recv_size() {
        return size_t(0);
    }

    void Connection::set_serv_name(const std::string& serv_name) {}

    std::string Connection::get_serv_name() const {
        return std::string("");
    }

    int Connection::get_connnection() const {
        return 5;
    }
}