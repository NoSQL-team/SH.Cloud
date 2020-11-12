#ifndef AUTH_SERVER_NOSOOL
#define AUTH_SERVER_NOSOOL

#include <string>
#include <map>
#include <pqxx/pqxx>
#include <netinet/in.h>

class DateBaseConnection
{
private:
    pqxx::connection _db;
public:
    DateBaseConnection() {};
    ~DateBaseConnection() {};
    std::string select(std::string request);
    int add_entry(std::string entry);
    int delete_entry(std::string request);
};

class ParserJSON
{
public:
    ParserJSON() {};
    std::map<std::string, std::string> parse(std::string str);
    std::string jsonfication(std::map<std::string, std::string> object);
};

class Connection
{
    int sock;
    struct sockaddr_in addr;
    int connect();
    int close();
public:
    Connection(uint16_t port, std::string ip) {};
    std::string sendRequest(std::string request);
    std::string getResponse();
};

class AuthService
{
private:
    DateBaseConnection _dbConn;
    ParserJSON _JSONparser;
    std::string requestHandlerIsAuth(std::string body);
    std::string requestHandlerAuth(std::string body);
    std::string requestHandlerLogout(std::string body);
    std::string requestHandlerAddUser(std::string body);
    std::string genToken(std::string nick, std::string email);
    void sendResponse();
    std::string getRequest();
public:
    AuthService() {};
    void run();
    void setServerHTTP(uint16_t port, std::string ip);
    void setServerQueue(uint16_t port, std::string ip);
};

#endif // AUTH_SERVER_NOSOOL