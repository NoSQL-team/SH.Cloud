//
// Created by Andrew Kireev on 06.11.2020.
//

#include "server_router.h"

namespace tcp_network {

	Server::Server(short port) : acceptor_(io_service_,
										ip::tcp::endpoint(ip::tcp::v4(), port)) {
		start_accept();
		io_service_.run();
	}

	void Server::start_accept() {
		auto new_session = std::make_shared<Session>(io_service_);
		acceptor_.async_accept(new_session->socket(),
							   boost::bind(&Server::handle_accept, this, new_session,
										   boost::asio::placeholders::error));
	}

	void Server::handle_accept(std::shared_ptr<Session> new_session,
					   const boost::system::error_code &error) {
		if (!error) {
			new_session->start(new_session);
		} else {
			new_session.reset();
		}

		start_accept();
	}

}