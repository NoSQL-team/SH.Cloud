//
// Created by lerakry on 05.12.2020.
//

#ifndef SERVERUSERS_SERVER_H
#define SERVERUSERS_SERVER_H

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "../includes/Session.h"

using boost::asio::ip::tcp;

class Server
{
public:
    Server(boost::asio::io_service& io_service, short port)
            : io_service_(io_service),
              acceptor_(io_service, tcp::endpoint(tcp::v4(), port));

private:
    void start_accept();

    void handle_accept(Session* new_session,
                       const boost::system::error_code& error);

    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
    UsersDatabase data_base_;
};

int main(int argc, char* argv[])
{
    try
    {

        boost::asio::io_service io_service;

        Server s(io_service, 8081);

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

#endif //SERVERUSERS_SERVER_H
