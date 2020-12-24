//
// Created by lerakrya on 10.12.2020.
//

#ifndef SERVERQUEUE_SESSION_H
#define SERVERQUEUE_SESSION_H

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <string>
#include <queue>

const int max_lenght = 10000;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::io_service& io_service, std::queue<std::string>& request);

    boost::asio::ip::tcp::socket& socket();

    void start(std::shared_ptr<Session> session);

    void send_request(std::string& request);


private:
    void handle_read(std::shared_ptr<Session> session);

    std::queue<std::string>& responses_;
    boost::asio::io_service& io_service_;
    boost::asio::ip::tcp::endpoint end_;
    boost::asio::ip::tcp::socket socket_;

    char data_[max_lenght];
};

#endif //SERVERQUEUE_SESSION_H
