//
// Created by Andrew Kireev on 08.11.2020.
//

#ifndef NOSKOOL_SERVER_ROUTER_H
#define NOSKOOL_SERVER_ROUTER_H

#include "server_interface.h"

#include <unordered_map>
#include <string>
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <memory>
#include "utilty.h"

namespace tcp_network {

	using namespace boost;
	using namespace boost::system;
	using namespace boost::asio;

	class Session : public std::enable_shared_from_this<Session> {
	public:
		Session(boost::asio::io_service &io_service)
				: socket_(io_service), data_{} {
		}

		ip::tcp::socket &socket() {
			return socket_;
		}

		void start(std::shared_ptr<Session> current_session) {
			socket_.async_read_some(boost::asio::buffer(data_, max_length),
									boost::bind(&Session::handle_read, this, current_session,
												boost::asio::placeholders::error,
												boost::asio::placeholders::bytes_transferred));
		}

	private:
		RequestDestination define_location() {
			std::string requst(data_);
			return parser_.get_destination(requst);
		}

		void handle_read(std::shared_ptr<Session> current_session, const system::error_code& error,
						 size_t bytes_transferred) {
			if (!error) {
//			boost::asio::async_write(socket_,
//									 boost::asio::buffer(data_, bytes_transferred),
//									 boost::bind(&Session::handle_write, this, current_session,
//												 boost::asio::placeholders::error));
				RequestDestination location = define_location();

				io_service service;
				ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"),
									  9999);
				ip::tcp::socket sock(service);
				sock.async_connect(ep, [&sock, this](const system::error_code& error) {
					if (!error) {
						std::cout << data_ << std::endl;
						boost::asio::write(sock, boost::asio::buffer(data_,
																	 strlen(data_)));

						std::cout << data_ << std::endl;
					}
				});
				service.run();
			} else {
				current_session.reset();
			}
		}

		void handle_write(std::shared_ptr<Session> current_session, const boost::system::error_code &error) {
			if (!error) {
				std::cout << std::string(data_);
				socket_.async_read_some(boost::asio::buffer(data_, max_length),
										boost::bind(&Session::handle_read, this, current_session,
													boost::asio::placeholders::error,
													boost::asio::placeholders::bytes_transferred));
			} else {
				current_session.reset();
			}
		}


		std::map<RequestDestination, Destination> servers_adrs_ =
				{{RequestDestination::POST_SERV, {"127.0.0.1", 9999}}};
		ip::tcp::socket socket_;
		ParseJson parser_;
		enum {
			max_length = 1024
		};
		char data_[max_length];
	};

	class Server {
	public:
		explicit Server(short port)
				:
				acceptor_(io_service_, ip::tcp::endpoint(ip::tcp::v4(), port)) {
			start_accept();
			io_service_.run();
		}

	private:
		void start_accept() {
			auto new_session = std::make_shared<Session>(io_service_);
			acceptor_.async_accept(new_session->socket(),
								   boost::bind(&Server::handle_accept, this, new_session,
											   boost::asio::placeholders::error));
		}

		void handle_accept(std::shared_ptr<Session> new_session,
						   const boost::system::error_code &error) {
			if (!error) {
				new_session->start(new_session);
			} else {
				new_session.reset();
			}

			start_accept();
		}

		boost::asio::io_service io_service_;
		ip::tcp::acceptor acceptor_;
	};

}

#endif //NOSKOOL_SERVER_ROUTER_H
