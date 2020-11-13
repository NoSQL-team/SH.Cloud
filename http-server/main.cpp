
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

int main(int argc, const char * argv[])
{
    HTTPServer server;
    server.run(9999);
    return 0;
}
