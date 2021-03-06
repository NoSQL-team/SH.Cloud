//
// Created by Andrew Kireev on 02.11.2020.
//

#ifndef NOSKOOL_CONNECTION_H
#define NOSKOOL_CONNECTION_H

#include "utilty.h"
#include "friends_data_base.h"

#include <memory>

#include <boost/bind.hpp>
#include <boost/asio.hpp>


namespace tcp_network {

	constexpr size_t max_length = 100000;

	class Session : public std::enable_shared_from_this<Session> {
	public:
		Session(boost::asio::io_service& io_service, FriendsDataBase& database);

		boost::asio::ip::tcp::socket& socket();

		void start(std::shared_ptr<Session> current_session);

		void send_response(std::string& response);

	private:

		void handle_read(std::shared_ptr<Session> current_session, const boost::system::error_code& error,
						 size_t bytes_transferred);

		boost::asio::ip::tcp::socket socket_;
		ParseJson parser_;
		FriendsDataBase& database_;
		boost::asio::io_service& io_service_;
		char data_[max_length];
	};

}

#endif //NOSKOOL_CONNECTION_H
