//
// Created by lerakrya on 10.12.2020.
//

#include <iostream>
#include <memory>
#include "Session.h"

using boost::asio::ip::tcp;

tcp::socket& Session::socket()
{
    return socket_;
}

void Session::start(std::shared_ptr<Session> session)
{
    std::cout << "start" << std::endl;
    for (size_t i = 0; i < 10000; i++) {
        data_[i] = '\0';
    }
    socket_.async_read_some(boost::asio::buffer(data_, 10000),
                            boost::bind(&Session::handle_read, this, session,
                                        boost::asio::placeholders::error));
}

void Session::handle_read(std::shared_ptr<Session> session, const boost::system::error_code& error)
{
    std::cout << "handle read" << std::endl;
    std::cout << data_ << std::endl;
    if (!error)
    {
        boost::asio::io_service service;
        tcp::socket socket(service);
        socket.async_connect(end_, [&socket, this] (const boost::system::error_code& err) {
            if(!err) {
                boost::asio::write(socket, boost::asio::buffer(data_, 10000));
            }
            else {
                std::cout << "lera" << std::endl;
            }
        });
        service.run();
    }
    else
    {
        session.reset();
    }
}
