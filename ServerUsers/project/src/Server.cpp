//
// Created by lerakry on 04.12.2020.
//

#include "Server.h"
#include <memory>
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;


//    Server::Server(boost::asio::io_service& io_service, short port)
//            : io_service_(io_service),
//              acceptor_(io_service,
//                        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
//    {
//        std::cout << "constr" << std::endl;
//        start_accept();
//    }

    Server::Server(short port) : acceptor_(io_service_,
                        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
        std::cout << "constr" << std::endl;
        start_accept();
        io_service_.run();
    }

    void Server::start_accept()
    {
        std::shared_ptr<Session> new_session = std::make_shared<Session>(io_service_, data_base_);

        std::cout << "Обрабатываем1" << std::endl;

        acceptor_.async_accept(new_session->socket(),
                               boost::bind(&Server::handle_accept, this, new_session,
                                           boost::asio::placeholders::error));
    }

    void Server::handle_accept(std::shared_ptr<Session> new_session,
                       const boost::system::error_code& error)
    {
        if (!error)
        {
            std::cout << "Обрабатываем" << std::endl;
            new_session->start();
        }
        else
        {
            new_session.reset();

        }

        start_accept();
    }



