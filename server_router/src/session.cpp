//
// Created by Andrew Kireev on 12.11.2020.
//


#include "session.h"
#include <unistd.h>
#include <iostream>
#include <stdexcept>

#include <boost/property_tree/ini_parser.hpp>


//=
//{{RequestDestination::POST_SERV, {"127.0.0.1", 9999}},
//{RequestDestination::FRIEND_SERV, {"127.0.0.1", 9998}},
//{RequestDestination::USER_SERV, {"127.0.0.1", 8883}},
//{RequestDestination::AUTH_SERV, {"127.0.0.1", 8884}}
//};

namespace tcp_network {

	Session::Session(boost::asio::io_service &io_service)
			: socket_(io_service), data_{} {
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("../router_settings.ini", pt);
		try {
			uint16_t http_port = pt.get<uint16_t>("http_serv.port");
			uint16_t friends_port = pt.get<uint16_t>("friends_queue.port");
			uint16_t post_port = pt.get<uint16_t>("post_queue.port");
			uint16_t users_port = pt.get<uint16_t>("users_queue.port");

			servers_adrs_.insert({RequestDestination::POST_SERV, {"127.0.0.1", post_port}});
			servers_adrs_.insert({RequestDestination::FRIEND_SERV, {"127.0.0.1", friends_port}});
			servers_adrs_.insert({RequestDestination::USER_SERV, {"127.0.0.1", users_port}});

		} catch (const std::exception& e) {

		}
	}

	ip::tcp::socket& Session::socket() {
		return socket_;
	}

	void Session::start(std::shared_ptr<Session> current_session) {
		socket_.async_receive(buffer(&data_[0], 5024),
								boost::bind(&Session::handle_read, this, current_session,
											boost::asio::placeholders::error,
											boost::asio::placeholders::bytes_transferred));
	}

	Destination Session::define_location() {
		try {
			std::string requst(data_);

			auto test = parser_.get_destination(requst);
			print_destination(test);
			Destination destination = servers_adrs_.at(test);
			return destination;
		} catch (std::out_of_range& e) {
			std::cerr << e.what() << std::endl;
			return {0, 0};
		}
	}

	void Session::handle_read(std::shared_ptr<Session> current_session, const system::error_code& error,
							  size_t bytes_transferred) {
		if (!error) {
			Destination destination = define_location();

			io_service service;
			ip::tcp::endpoint ep( ip::address::from_string(destination.ip),
								  destination.port);
			ip::tcp::socket sock(service);
			sock.async_connect(ep, [&sock, this](const system::error_code& error) {
				if (!error) {
					std::string requst(data_);
					boost::asio::write(sock, boost::asio::buffer(requst.c_str(), strlen(data_)));

					std::cout << data_ << std::endl;
				}
			});
			service.run();
		} else {
			current_session.reset();
		}
	}
}
