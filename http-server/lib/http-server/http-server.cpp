#include "http-server.hpp"

void HTTPServer::acceptAndRun(ip::tcp::acceptor& acceptor, io_service& io_service)
{
    std::shared_ptr<Session> sesh = std::make_shared<Session>(io_service);

    acceptor.async_accept(
        sesh->socket,
        [sesh, &acceptor, &io_service, this](const error_code& accept_error)
        {
            acceptAndRun(acceptor, io_service);
            if(!accept_error) {
                Session::handleRequest(sesh);
            }
        }
    );
}

void HTTPServer::run(uint16_t port)
{
    io_service io_service;
    ip::tcp::endpoint endpoint{ip::tcp::v4(), port};
    ip::tcp::acceptor acceptor{io_service, endpoint};
    
    acceptor.listen();
    acceptAndRun(acceptor, io_service);
    
    io_service.run();
}