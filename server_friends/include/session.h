//
// Created by Andrew Kireev on 02.11.2020.
//

#ifndef NOSKOOL_CONNECTION_H
#define NOSKOOL_CONNECTION_H


#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "utilty.h"
#include "friends_data_base.h"

namespace tcp_network {

	using namespace boost;
	using namespace boost::system;
	using namespace boost::asio;

	class Session : public std::enable_shared_from_this<Session> {
	public:
		Session(boost::asio::io_service &io_service, FriendsDataBase& database_);

		ip::tcp::socket &socket();

		void start(std::shared_ptr<Session> current_session);

		void send_response(std::string& respones);

	private:
		Destination define_location();

		void handle_read(std::shared_ptr<Session> current_session, const system::error_code& error,
						 size_t bytes_transferred);

		void handle_write(std::shared_ptr<Session> current_session, const boost::system::error_code &error);

		void  handle_database_req(std::shared_ptr<Session> current_session, const boost::system::error_code &error);


		std::map<RequestDestination, Destination> servers_adrs_ =
				{{RequestDestination::POST_SERV, {"127.0.0.1", 9999}},
				 {RequestDestination::FRIEND_SERV, {"127.0.0.1", 9998}},
				 {RequestDestination::UNKNOWN, {"0.0.0.0", 0}},
				 {RequestDestination::HTTP_SERV, {"127.0.0.1", 9999}}};
		ip::tcp::socket socket_;
		ParseJson parser_;
		FriendsDataBase& database_;
		boost::asio::io_service& io_service_;
		enum {
			max_length = 1024
		};
		char data_[max_length];
	};

}

#endif //NOSKOOL_CONNECTION_H
