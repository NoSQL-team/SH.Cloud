#include <boost/asio.hpp>
#include <string>
#include <memory>
#include <thread>
#include "lib/auth-server/auth-server.hpp"

using namespace boost;
using namespace boost::system;
using namespace boost::asio;

// DateBaseConnection* responsesHandler = DateBaseConnection::getInstance();
// std::mutex DateBaseConnection::_mutex;
size_t number = 0;


int main(int argc, const char * argv[])
{
    AuthServer server;
    server.run(9999);
    return 0;
}