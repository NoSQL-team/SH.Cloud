#include "include/server.h"


int main() {

    TCPServer server(3333);  // boost::lexical_cast<std::uint16_t>(argv[1])

    return 0;
}
