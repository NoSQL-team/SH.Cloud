//
// Created by lerakry on 04.12.2020.
//

#ifndef SERVERUSERS_SESSION_H
#define SERVERUSERS_SESSION_H


#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "UsersDatabase.h"

using boost::asio::ip::tcp;

class Session
{
public:
    Session(boost::asio::io_service& io_service, UsersDatabase& data_base)
            : socket_(io_service), io_service_(io_service), data_base_(data_base)
    {}

//    Session(boost::asio::io_service& io_service)
//            : io_service_(io_service), socket_(io_service)
//    {}

    tcp::socket& socket();

    void send_answer(std::string answer);

    void start();

private:
    void handle_read(const boost::system::error_code& error,
                     size_t bytes_transferred);

    void handle_write(const boost::system::error_code& error);

    boost::asio::io_service& io_service_;
    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
    UsersDatabase& data_base_;
};


#endif //SERVERUSERS_SESSION_H
