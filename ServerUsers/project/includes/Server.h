//
// Created by lerakry on 05.12.2020.
//

#ifndef SERVERUSERS_SERVER_H
#define SERVERUSERS_SERVER_H

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "../includes/Session.h"
#include "../includes/UsersDatabase.h"

using boost::asio::ip::tcp;

class Server
{
public:
    Server(boost::asio::io_service& io_service, short port);

private:
    void start_accept();

    void handle_accept(Session* new_session,
                       const boost::system::error_code& error);

    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
    UsersDatabase data_base_;
};

#endif //SERVERUSERS_SERVER_H
