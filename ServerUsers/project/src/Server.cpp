//
// Created by lerakry on 04.12.2020.
//

#include "../includes/Server.h"
#include "../includes/Session.h"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;


    Server::Server(boost::asio::io_service& io_service, short port)
            : io_service_(io_service),
              acceptor_(io_service,
                        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
        std::cout << "constr" << std::endl;
        start_accept();
    }

    void Server::start_accept()
    {
//        Session* new_session = new Session(io_service_, data_base_);
        Session* new_session = new Session(io_service_, data_base_);

        std::cout << "Обрабатываем1" << std::endl;

//        acceptor_.accept();
//
        acceptor_.async_accept(new_session->socket(),
                               boost::bind(&Server::handle_accept, this, new_session,
                                           boost::asio::placeholders::error));
//        handle_accept(new_session, boost::system::error_code());

    }

    void Server::handle_accept(Session* new_session,
                       const boost::system::error_code& error)
    {
        if (!error)
        {
            std::cout << "Обрабатываем" << std::endl;
            new_session->start();
        }
        else
        {
            delete new_session;
        }

        start_accept();
    }



