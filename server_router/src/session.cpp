//
// Created by Andrew Kireev on 12.11.2020.
//


#include "session.h"
#include <unistd.h>
#include <iostream>

namespace tcp_network {

	Session::Session(boost::asio::io_service &io_service)
			: socket_(io_service), data_{} {
	}

	ip::tcp::socket& Session::socket() {
		return socket_;
	}

	void Session::start(std::shared_ptr<Session> current_session) {
		socket_.async_read_some(boost::asio::buffer(data_, max_length),
								boost::bind(&Session::handle_read, this, current_session,
											boost::asio::placeholders::error,
											boost::asio::placeholders::bytes_transferred));
	}

	RequestDestination Session::define_location() {
		std::string requst(data_);
		return parser_.get_destination(requst);
	}

	void Session::handle_read(std::shared_ptr<Session> current_session, const system::error_code& error,
							  size_t bytes_transferred) {
		if (!error) {
			RequestDestination location = define_location();

			io_service service;
			ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"),
								  9999);
			ip::tcp::socket sock(service);
			sock.async_connect(ep, [&sock, this](const system::error_code& error) {
				if (!error) {
					std::cout << data_ << std::endl;
					boost::asio::write(sock, boost::asio::buffer(data_,
																 strlen(data_)));

					std::cout << data_ << std::endl;
				}
			});
			service.run();
		} else {
			current_session.reset();
		}
	}

	void Session::handle_write(std::shared_ptr<Session> current_session, const boost::system::error_code &error) {
		if (!error) {
			std::cout << std::string(data_);
			socket_.async_read_some(boost::asio::buffer(data_, max_length),
									boost::bind(&Session::handle_read, this, current_session,
												boost::asio::placeholders::error,
												boost::asio::placeholders::bytes_transferred));
		} else {
			current_session.reset();
		}
	}

}
