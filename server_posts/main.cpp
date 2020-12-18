#include "include/server.h"


int main() {
    io::io_context io_context;
    TCPServer server(io_context, 3333);  // boost::lexical_cast<std::uint16_t>(argv[1])
    server.add_endpoint();
    io_context.run();
    return 0;
}
