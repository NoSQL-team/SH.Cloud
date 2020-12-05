//
// Created by lerakry on 03.12.2020.
//
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <memory>
#include "../includes/Session.h"
#include "../includes/HandlerUser.h"

using boost::asio::ip::tcp;

tcp::socket& Session::socket()
{
    return socket_;
}

void Session::start()
{
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
                            boost::bind(&Session::handle_read, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void Session::handle_read(const boost::system::error_code& error,
                 size_t bytes_transferred)
{
    if (!error)
    {
        auto handler = std::make_shared<HandlerUser>(io_service_, *this, data_base_);
//            io_service_.post([](){
            auto str = std::string(data_);
            handler->handle_request(str);
//            });
//            boost::asio::async_write(socket_,
//                                     boost::asio::buffer(data_, bytes_transferred),
//                                     boost::bind(&Session::handle_write, this,
//                                                 boost::asio::placeholders::error));
    }
    else
    {
        delete this;
    }
}

void Session::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                boost::bind(&Session::handle_read, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        delete this;
    }
}


