//
// Created by lerakry on 04.12.2020.
//

#ifndef SERVERUSERS_SESSION_H
#define SERVERUSERS_SESSION_H


#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "UsersDatabase.h"

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::io_service& io_service, UsersDatabase& data_base)
            : socket_(io_service), io_service_(io_service), data_base_(data_base)
    {}

    boost::asio::ip::tcp::socket& socket();

    void send_answer(std::string& answer);

    void start();

private:
	void handle_read(std::shared_ptr<Session> session,
						   const boost::system::error_code& error);


    boost::asio::io_service& io_service_;
    boost::asio::ip::tcp::socket socket_;
    int max_length = 1024;
    char data_[1024];
//    std::string data_;
    UsersDatabase& data_base_;
};


#endif //SERVERUSERS_SESSION_H
