#include "lib/auth-server/auth-server.hpp"

int main(int argc, const char * argv[])
{
    AuthService service;

    service.setServerHTTP(1, "");
    service.setServerQueue(1, "");
    service.run();

    return 0;
}
