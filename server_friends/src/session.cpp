//
// Created by Andrew Kireev on 11.11.2020.
//

//#define _GLIBCXX_USE_CXX11_ABI 0

#include "session.h"
#include "requst_handler.h"
#include <iostream>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;

namespace tcp_network {

	Session::Session(boost::asio::io_service& io_service, FriendsDataBase& database)
			: io_service_(io_service), socket_(io_service), database_(database), data_{} {
	}

	ip::tcp::socket& Session::socket() {
		return socket_;
	}

	void Session::start(std::shared_ptr<Session> current_session) {
		for (size_t i = 0; i < max_length; i++) {
        	data_[i] = '\0';
    	}
		socket_.async_read_some(boost::asio::buffer(data_, max_length),
								boost::bind(&Session::handle_read, this, current_session,
											boost::asio::placeholders::error,
											boost::asio::placeholders::bytes_transferred));
	}

	void Session::handle_read(std::shared_ptr<Session> current_session, const system::error_code& error,
							  size_t bytes_transferred) {
		if (!error) {
			std::string req(data_);
			std::map<std::string, std::string> request = parser_.parse(req);
			auto handler = std::make_shared<RequestHandler>(io_service_, database_,
												   shared_from_this(), request);
			handler->handle_request();
		} else {
			current_session.reset();
		}
	}

	void Session::send_response(std::string& respones) {
		Destination destination = {"127.0.0.1", 9999};
		io_service service;
		ip::tcp::endpoint ep( ip::address::from_string(destination.ip),
							  destination.port);
		ip::tcp::socket sock(service);
		sock.async_connect(ep, [&sock, this, &respones](const system::error_code& error) {
			if (!error) {
				boost::asio::write(sock, boost::asio::buffer(respones, respones.size()));
			} else {
			}
		});
		service.run();
	}
}
