
#include <boost/asio.hpp>
#include <string>
#include <memory>
#include <thread>
#include "lib/http-server/http-server.hpp"

using namespace boost;
using namespace boost::system;
using namespace boost::asio;

std::vector<std::string> addrs = {};
ResponsesHandler* responsesHandler = ResponsesHandler::getInstance();
std::mutex ResponsesHandler::_mutex;
size_t number = 0;

void accept_and_run(ip::tcp::acceptor& acceptor, io_service& io_service)
{
    std::shared_ptr<Session> sesh = std::make_shared<Session>(io_service);

    acceptor.async_accept(
        sesh->socket,
        [sesh, &acceptor, &io_service](const error_code& accept_error)
        {
            accept_and_run(acceptor, io_service);
            if(!accept_error) {
                Session::handleRequest(sesh);
            }
        }
    );
}

int main(int argc, const char * argv[])
{
    io_service io_service;
    ip::tcp::endpoint endpoint{ip::tcp::v4(), 9999};
    ip::tcp::acceptor acceptor{io_service, endpoint};
    
    acceptor.listen();
    accept_and_run(acceptor, io_service);
    
    io_service.run();

    return 0;
}
