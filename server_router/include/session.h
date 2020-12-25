//
// Created by Andrew Kireev on 02.11.2020.
//

#ifndef NOSKOOL_CONNECTION_H
#define NOSKOOL_CONNECTION_H

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "utilty.h"

namespace tcp_network {

	using namespace boost;
	using namespace boost::system;
	using namespace boost::asio;

	class Session : public std::enable_shared_from_this<Session> {
	public:
		explicit Session(boost::asio::io_service& io_service);

		ip::tcp::socket &socket();

		void start(std::shared_ptr<Session> current_session);

	private:
		Destination define_location();

		void handle_read(std::shared_ptr<Session> current_session, const system::error_code& error);

		std::map<RequestDestination, Destination> servers_adrs_;
		ip::tcp::socket socket_;
		ParseJson parser_;
		static constexpr int max_length = 100000;
		char data_[max_length];
	};

}


#endif //NOSKOOL_CONNECTION_H
