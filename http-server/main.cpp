#include <boost/asio.hpp>
#include <string>
#include <memory>
#include "lib/http-server/http-server.hpp"
#include <boost/thread/thread.hpp>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;

std::vector<std::string> addrs = {};
ResponsesHandler* responsesHandler = ResponsesHandler::getInstance();
std::mutex ResponsesHandler::_mutex;
size_t number = 0;

int main(int argc, const char * argv[])
{
    boost::asio::io_service io_service_;
    HTTPServer server(io_service_);

    boost::thread_group tgroup;
    unsigned corenumber = boost::thread::hardware_concurrency();
    for(unsigned i = 0; i < corenumber; ++i){
        tgroup.create_thread(boost::bind(&boost::asio::io_service::run, &io_service_));
    }
    tgroup.join_all();
    return 0;
}
