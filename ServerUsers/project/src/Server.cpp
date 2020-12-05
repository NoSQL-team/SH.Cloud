//
// Created by lerakry on 04.12.2020.
//

#include "../includes/Server.h.h"

using boost::asio::ip::tcp;

class Server
{
public:
    Server(boost::asio::io_service& io_service, short port)
            : io_service_(io_service),
              acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
    {
        start_accept();
    }

private:
    void start_accept()
    {
        Session* new_session = new Session(io_service_, data_base_);
        acceptor_.async_accept(new_session->socket(),
                               boost::bind(&Server::handle_accept, this, new_session,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(Session* new_session,
                       const boost::system::error_code& error)
    {
        if (!error)
        {
            new_session->start();
        }
        else
        {
            delete new_session;
        }

        start_accept();
    }

    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
    UsersDatabase data_base_;
};

int main(int argc, char* argv[])
{
    try
    {

        boost::asio::io_service io_service;

        Server s(io_service, 8081);

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

