//
// Created by Andrew Kireev on 03.12.2020.
//


#include <utility>

#include "requst_handler.h"

namespace tcp_network {

	RequestHandler::RequestHandler(boost::asio::io_service& io_service, FriendsDataBase& database,
								   std::shared_ptr<Session> session,
								   std::map<std::string, std::string>& request) :
								io_service_(io_service), session_(std::move(session)), database_(database),
								request_(request) {}

	void RequestHandler::handle_request() {
		if (request_.count("type") && request_["type"] == "add") {
//			io_service_.post([this](){
				handle_add();
//			});
		} else if (request_.count("type") && request_["type"] == "is_friend") {
//			io_service_.post([this](){
				handle_is_friend();
//			});
		} else if (request_.count("type") && request_["type"] == "delete") {
//			io_service_.post([this](){
				handle_delete();
//			});
		} else if (request_.count("type") && request_["type"] == "get_all") {
//			io_service_.post([this](){
				handle_get_all_friends();
//			});
		}
	}

	void RequestHandler::handle_add() {
		bool result = database_.add_friend(std::atoi(request_["user_1"].c_str()),
					   std::atoi(request_["user_2"].c_str()));

		std::string response = form_post_response(result);
		session_->send_response(response);
	}

	void RequestHandler::handle_get_all_friends() {
		std::vector<int> all_friends = database_.get_all_friends(
				std::atoi(request_["user_1"].c_str()));

		std::string string_respones = form_get_fr_response(all_friends);
		session_->send_response(string_respones);
	}

	void RequestHandler::handle_delete() {
		bool result = database_.delete_friend(std::atoi(request_["user_1"].c_str()),
											 std::atoi(request_["user_2"].c_str()));

		std::string response = form_post_response(result);
		session_->send_response(response);
	}

	void RequestHandler::handle_is_friend() {
		bool result = database_.is_friend(std::atoi(request_["user_1"].c_str()),
										  std::atoi(request_["user_2"].c_str()));

		std::string response = form_post_response(result);
		session_->send_response(response);
	}

	std::string RequestHandler::form_post_response(bool result) {
		std::string response = "{ \"response\": ";
		if (result)
			response += "true";
		else
			response += "false";
		response += " }";
		return response;
	}

	std::string RequestHandler::form_get_fr_response(const std::vector<int>& friends) {
		std::stringstream response;
		response << "{\n \"response\": ";
		response << "\"true\"";
		response << ",\n \"data\": [";

		int i = 0;
		for (auto it : friends) {
			if (i != 0)
				response << ", ";
			response << it;
			i = 1;
		}
		response << "]\n}";
		return response.str();
	}
}
