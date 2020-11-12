//
// Created by amartery on 08.11.2020.
//

#ifndef NOSKOOL_UTILTY_POSTS_H
#define NOSKOOL_UTILTY_POSTS_H

#include <map>


namespace tcp_server {

    class Socket {
    public:
        explicit Socket(int& fd) noexcept;
        Socket() = default;
        explicit Socket(Socket&& other) noexcept;

        ~Socket() noexcept;

        Socket& operator=(const int fd);

        virtual void close() noexcept;

        int get() const;

    private:
        int socket_ = -1;
    };

    enum RequestDestination {
        FRIEND_SERV,
        POST_SERV,
        AUTH_SERV,
        USER_SERV
    };


    class JsonParser {
    public:

        JsonParser() = default;

        RequestDestination get_destination(std::string& request);

        std::map<std::string, std::string> parse(std::string& request);

        std::map<std::string, std::string> get_request() const;

    private:
        std::map<std::string, std::string> request_;
    };

}

#endif  // NOSKOOL_UTILTY_POSTS_H