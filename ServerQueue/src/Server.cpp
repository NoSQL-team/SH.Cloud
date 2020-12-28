//
// Created by lerakrya on 10.12.2020.
//

#include "Server.h"
#include <iostream>

using boost::asio::ip::tcp;

Server::Server(short port) : acceptor_(io_service_,
                                       boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    start_accept();
    io_service_.run();
}

void Server::start_accept()
{
    if (!queue_response.empty()) {
        std::shared_ptr<Session> new_session_1 = std::make_shared<Session>(io_service_, queue_response);
        send_request(new_session_1);
    }
    std::shared_ptr<Session> new_session = std::make_shared<Session>(io_service_, queue_response);
    acceptor_.accept(new_session->socket());
    handle_accept(new_session);
}

void Server::send_request(std::shared_ptr<Session> new_session) {
    auto req = queue_response.front();
    queue_response.pop();
    new_session->send_request(req);
}

void Server::handle_accept(std::shared_ptr<Session> new_session)
{
    new_session->start(new_session);
    start_accept();
}
