//
// Created by Andrew Kireev on 03.12.2020.
//


#include <utility>

#include "requst_handler.h"

namespace tcp_network {

	RequestHandler::RequestHandler(boost::asio::io_service& io_service, FriendsDataBase& database,
								   std::shared_ptr<Session> session,
								   std::map<std::string, std::string>& request) :
								io_service_(io_service), session_(std::move(session)), database_(database), request_(request) {}

	void RequestHandler::handle_request() {
		if (request_.count("type") && request_["type"] == "add") {
//			io_service_.post([this](){
				handle_add();
//			});
		} else if (request_.count("type") && request_["type"] == "is_friend") {
			io_service_.post([this](){
				handle_is_friend();
			});
		} else if (request_.count("type") && request_["type"] == "delete") {
			io_service_.post([this](){
				handle_delete();
			});
		} else if (request_.count("type") && request_["type"] == "get_all") {
			io_service_.post([this](){
				handle_get_all_friends();
			});
		}
	}

	void RequestHandler::handle_add() {
		int result = database_.add_friend(std::atoi(request_["user_1"].c_str()),
					   std::atoi(request_["user_2"].c_str()));
		std::string str_res = std::to_string(result);
		session_->send_response(str_res);
	}

	void RequestHandler::handle_get_all_friends() {
		std::string response = "200 data: some friend";
		session_->send_response(response);
	}

	void RequestHandler::handle_delete() {

	}

	void RequestHandler::handle_is_friend() {

	}

}
