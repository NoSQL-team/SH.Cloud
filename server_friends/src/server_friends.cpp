//
// Created by Andrew Kireev on 02.11.2020.
//

#include "server_friends.h"
#include <memory>
//#include <boost/log/trivial.hpp>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;

namespace tcp_network {

	Server::Server(short port, std::map<std::string, std::string>& db_settings) : acceptor_(io_service_,
										   ip::tcp::endpoint(ip::tcp::v4(), port)), database_(db_settings) {
		start_accept();
		io_service_.run();
	}

	void Server::start_accept() {
		auto new_session = std::make_shared<Session>(io_service_, database_);
		acceptor_.async_accept(new_session->socket(),
							   boost::bind(&Server::handle_accept, this, new_session,
										   boost::asio::placeholders::error));
	}

	void Server::handle_accept(std::shared_ptr<Session> new_session,
							   const boost::system::error_code &error) {
		if (!error) {
			new_session->start(new_session);
		} else {
//			BOOST_LOG_TRIVIAL(info) << "Connection closed " << error.message();
			new_session.reset();
		}

		start_accept();
	}

}