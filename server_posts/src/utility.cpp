//
// Created by amartery on 08.11.2020.
//

#include <zconf.h>  // компрессия и сжатие
#include "utility.h"
#include <string>
#include <map>

namespace tcp_server {

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


    RequestDestination JsonParser::get_destination(std::string& request) {
        return RequestDestination::AUTH_SERV;
    }

    std::map<std::string, std::string> JsonParser::parse(std::string& request) {
        request_.insert({"email", "test@gmail.com"});
        request_.insert({"password", "test"});
        request_.insert({"username", "test123"});
        return request_;
    }

    std::map<std::string, std::string> JsonParser::get_request() const {
        return request_;
    }
}