#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "lib/auth-server/auth-server.hpp"

#include <iostream>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;

void runServer() 
{
    boost::asio::io_service io_service_;
    AuthServer server(io_service_, 9992);

    boost::thread_group tgroup;
    unsigned corenumber = boost::thread::hardware_concurrency();
    for(size_t i = 0; i < corenumber; i++){
        tgroup.create_thread(boost::bind(&boost::asio::io_service::run, &io_service_));
    }
    tgroup.join_all();
}

int main(int argc, const char * argv[])
{
    try
    {
        runServer();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }   

    return 0;
}