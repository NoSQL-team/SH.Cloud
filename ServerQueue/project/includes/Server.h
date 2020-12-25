//
// Created by lerakrya on 10.12.2020.
//

#ifndef SERVERQUEUE_SERVER_H
#define SERVERQUEUE_SERVER_H

#include "Session.h"
#include <queue>

class Server
{
public:
    explicit Server(short port);

private:
    std::queue<std::string> queue_response;
    void start_accept();

    void send_request(std::shared_ptr<Session> new_session);

    void handle_accept(std::shared_ptr<Session> new_session);

    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
};

#endif //SERVERQUEUE_SERVER_H
