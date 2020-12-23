//
// Created by lerakrya on 10.12.2020.
//

#ifndef SERVERQUEUE_SESSION_H
#define SERVERQUEUE_SESSION_H

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <string>

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::io_service& io_service)
            : socket_(io_service), io_service_(io_service)
    {
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("../queue_settings.ini", pt);
		end_ = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"),
										pt.get<int>("destination.port"));
    }

    boost::asio::ip::tcp::socket& socket();

    void start(std::shared_ptr<Session> session);


private:
    void handle_read(std::shared_ptr<Session> session, const boost::system::error_code& error);


    boost::asio::io_service& io_service_;
    boost::asio::ip::tcp::endpoint end_;
    boost::asio::ip::tcp::socket socket_;

    char data_[10000];
};

#endif //SERVERQUEUE_SESSION_H
