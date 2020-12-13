//
// Created by lerakrya on 10.12.2020.
//

#include "Server.h"

using boost::asio::ip::tcp;

Server::Server(short port) : acceptor_(io_service_,
                                       boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    std::cout << "constr" << std::endl;
    start_accept();
    io_service_.run();
}

void Server::start_accept()
{
    std::shared_ptr<Session> new_session = std::make_shared<Session>(io_service_);

    std::cout << "Обрабатываем1" << std::endl;
    if (!queue_response.empty()) {
        std::shared_ptr<Session> new_session_1 = std::make_shared<Session>(io_service_);
        send_request(new_session_1);
    }
    std::cout << "Обрабатываем2" << std::endl;
    acceptor_.async_accept(new_session->socket(),
                           boost::bind(&Server::handle_accept, this, new_session,
                                       boost::asio::placeholders::error));
    std::cout << "Обрабатываем3" << std::endl;
}

void Server::send_request(std::shared_ptr<Session> new_session) {
        std::cout << "Обрабатываем" << std::endl;

        auto req = queue_response.front();
        queue_response.pop();
        start_accept();
}

void Server::handle_accept(std::shared_ptr<Session> new_session,
                           const boost::system::error_code& error)
{
    if (!error)
    {
        std::cout << "Обрабатываеммм" << std::endl;
        new_session->start(new_session);
    }
    else
    {
        new_session.reset();
    }

    start_accept();
}


