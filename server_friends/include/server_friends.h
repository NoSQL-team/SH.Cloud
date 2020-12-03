//
// Created by Andrew Kireev on 02.11.2020.
//

#ifndef NOSKOOL_SERVER_FRIENDS_H
#define NOSKOOL_SERVER_FRIENDS_H

#include "friends_data_base.h"
#include <unordered_map>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <session.h>

namespace tcp_network {

	using namespace boost;
	using namespace boost::system;
	using namespace boost::asio;


	class Server {
	public:
		explicit Server(short port);

	private:
		void start_accept();

		void handle_accept(std::shared_ptr<Session> new_session,
						   const boost::system::error_code &error);

		boost::asio::io_service io_service_;
		ip::tcp::acceptor acceptor_;
		FriendsDataBase database_;
	};

}

#endif //NOSKOOL_SERVER_FRIENDS_H
