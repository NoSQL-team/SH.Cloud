//
// Created by Andrew Kireev on 03.12.2020.
//

#ifndef TESTS_REQUST_HANDLER_H
#define TESTS_REQUST_HANDLER_H

#include "utilty.h"
#include "session.h"
#include "friends_data_base.h"

namespace tcp_network {

	class RequestHandler {
	public:
		RequestHandler(boost::asio::io_service& io_service, FriendsDataBase& database,
				 std::shared_ptr<Session> session,
				 std::map<std::string, std::string>& request);

		void handle_request();

	private:
		void handle_add();

		void handle_delete();

		void handle_is_friend();

		void handle_get_all_friends();

		std::string form_post_response(bool result);

		std::string form_get_fr_response(const std::vector<int>& friends);

		boost::asio::io_service& io_service_;
		std::shared_ptr<Session> session_;
		FriendsDataBase& database_;
		std::map<std::string, std::string> request_;
	};

}

#endif //TESTS_REQUST_HANDLER_H
