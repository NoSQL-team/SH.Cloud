//
// Created by Andrew Kireev on 11.11.2020.
//

#define _GLIBCXX_USE_CXX11_ABI 0

#include "session.h"
#include "requst_handler.h"

#include <boost/log/trivial.hpp>



using namespace boost;
using namespace boost::system;
using namespace boost::asio;


static const std::map<tcp_network::RequestDestination, tcp_network::Destination> servers_adrs_ =
		{{tcp_network::RequestDestination::POST_SERV, {"127.0.0.1", 9997}},
		 {tcp_network::RequestDestination::FRIEND_SERV, {"127.0.0.1", 9998}},
		 {tcp_network::RequestDestination::UNKNOWN, {"0.0.0.0", 0}},
		 {tcp_network::RequestDestination::HTTP_SERV, {"127.0.0.1", 9999}}};

namespace tcp_network {

	Session::Session(boost::asio::io_service& io_service, FriendsDataBase& database)
			: io_service_(io_service), socket_(io_service), database_(database), data_{} {
	}

	ip::tcp::socket& Session::socket() {
		return socket_;
	}

	void Session::start(std::shared_ptr<Session> current_session) {
		socket_.async_read_some(boost::asio::buffer(data_, max_length),
								boost::bind(&Session::handle_read, this, current_session,
											boost::asio::placeholders::error,
											boost::asio::placeholders::bytes_transferred));
	}

	Destination Session::define_location() {
		try {
			std::string requst(data_);
			auto test = parser_.get_destination(requst);
			print_destination(test);
			Destination destination = servers_adrs_.at(test);
			return destination;
		} catch (std::out_of_range& e) {
//			BOOST_LOG_TRIVIAL(error) << "error parsing destination " << e.what();
			return {0, 0};
		}
	}

	void Session::handle_read(std::shared_ptr<Session> current_session, const system::error_code& error,
							  size_t bytes_transferred) {
		if (!error) {
			std::string req(data_);
			std::map<std::string, std::string> request = parser_.parse(req);
			auto handler = std::make_shared<RequestHandler>(io_service_, database_,
												   shared_from_this(), request);

//			io_service_.post([handler, this]() {
				handler->handle_request();
//			});

		} else {
//			BOOST_LOG_TRIVIAL(error) << error.message();
			current_session.reset();
		}
	}

	void Session::send_response(std::string& respones) {
		Destination destination = servers_adrs_.at(RequestDestination::HTTP_SERV);
		io_service service;
		ip::tcp::endpoint ep( ip::address::from_string(destination.ip),
							  destination.port);
		ip::tcp::socket sock(service);
		sock.async_connect(ep, [&sock, this, &respones](const system::error_code& error) {
			if (!error) {
				boost::asio::write(sock, boost::asio::buffer(respones, respones.size()));
			} else {
//				BOOST_LOG_TRIVIAL(error) << error.message();
			}
		});
		service.run();
	}
}
