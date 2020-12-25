//
// Created by lerakrya on 10.12.2020.
//

#include <iostream>
#include <memory>
#include "Session.h"

using boost::asio::ip::tcp;

void Session::send_request(std::string& request) {
    std::cout << "Пришли отправлять" << std::endl;
    boost::asio::io_service service;
    tcp::socket socket(service);
    socket.async_connect(end_, [&socket, this, &request] (const boost::system::error_code& err) {
        if(!err) {
            boost::asio::write(socket, boost::asio::buffer(request.c_str(), request.size()));
        }
        else {
            std::cerr << "Ошибка подключения Session::send_request" << std::endl;
        }
    });
    service.run();
}

Session::Session(boost::asio::io_service& io_service, std::queue<std::string>& request)
: socket_(io_service), io_service_(io_service), responses_(request)
{
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("../queue_settings.ini", pt);
    end_ = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"),
                                          pt.get<int>("destination.port"));
}

tcp::socket& Session::socket()
{
    return socket_;
}

void Session::start(std::shared_ptr<Session> session)
{
    std::cout << "start" << std::endl;
    socket_.read_some(boost::asio::buffer(data_, max_lenght));
    handle_read(session);
}

void Session::handle_read(std::shared_ptr<Session> session) // const boost::system::error_code& error)
{
    responses_.push(std::string(data_));
}


