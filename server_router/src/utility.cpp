//
// Created by Andrew Kireev on 12.11.2020.
//

#include <zconf.h>
#include "utilty.h"
#include <string>
#include <map>

namespace tcp_network {

    Socket::Socket(int& fd) noexcept : socket_(fd){}

    Socket::Socket(Socket&& other) noexcept :
            socket_(std::exchange(other.socket_, -1)){}

    Socket::~Socket() noexcept{
        close();
    }

    void Socket::close() noexcept {
        if(socket_ != -1) {
            try{
                ::close(socket_);
            } catch (...) {
            }
        }
        socket_ = -1;
    }

    Socket& Socket::operator=(const int fd){
        close();
        socket_ = fd;
        return *this;
    }

    int Socket::get() const {
        return socket_;
    }




    RequestDestination ParseJson::get_destination(std::string& request) {
        return RequestDestination::POST_SERV;
    }

    std::map<std::string, std::string> ParseJson::parse(std::string& request) {
        request_.insert({"email", "UUU@gmail.com"});
        request_.insert({"password", "qwerty"});
        request_.insert({"username", "Filechka322"});
        return request_;
    }

    std::map<std::string, std::string> ParseJson::get_request() const {
        return request_;
    }
}
