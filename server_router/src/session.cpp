//
// Created by Andrew Kireev on 12.11.2020.
//

#include <stdexcept>

//#include <boost/log/trivial.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "session.h"

namespace tcp_network {

	Session::Session(boost::asio::io_service &io_service)
			: socket_(io_service), data_{} {
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("../router_settings.ini", pt);
		try {
			uint16_t friends_port = pt.get<uint16_t>("friends_queue.port");
			uint16_t post_port = pt.get<uint16_t>("post_queue.port");
			uint16_t users_port = pt.get<uint16_t>("users_queue.port");

			servers_adrs_.insert({RequestDestination::POST_SERV, {"127.0.0.1", post_port}});
			servers_adrs_.insert({RequestDestination::FRIEND_SERV, {"127.0.0.1", friends_port}});
			servers_adrs_.insert({RequestDestination::USER_SERV, {"127.0.0.1", users_port}});

		} catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
//			BOOST_LOG_TRIVIAL(error) << e.what();
		}
	}

	ip::tcp::socket& Session::socket() {
		return socket_;
	}

	void Session::start(std::shared_ptr<Session> current_session) {
		socket_.async_receive(buffer(&data_[0], max_length),
								boost::bind(&Session::handle_read, this, current_session,
											boost::asio::placeholders::error));
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
//			BOOST_LOG_TRIVIAL(error) << e.what();
			return {0, 0};
		}
	}

	void Session::handle_read(std::shared_ptr<Session> current_session, const system::error_code& error) {
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
				}
			});
			service.run();
		} else {
			current_session.reset();
			std::cerr << error.message() << std::endl;
//			BOOST_LOG_TRIVIAL(error) << error.message();
		}
	}
}
