#include "lib/auth-server/auth-server.hpp"

int main(int argc, const char * argv[])
{
    AuthService service;

    service.setServerHTTP("", "");
    service.setServerQueue("", "");
    service.run();

    return 0;
}
