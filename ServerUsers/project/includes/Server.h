//
// Created by lerakry on 05.12.2020.
//

#ifndef SERVERUSERS_SERVER_H
#define SERVERUSERS_SERVER_H

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "Session.h"
#include "UsersDatabase.h"


class Server
{
public:
//    Server(boost::asio::io_service& io_service, short port);
    explicit Server(short port);

private:
    void start_accept();

    void handle_accept(std::shared_ptr<Session> new_session,
                       const boost::system::error_code& error);

    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    UsersDatabase data_base_;
};

#endif //SERVERUSERS_SERVER_H
