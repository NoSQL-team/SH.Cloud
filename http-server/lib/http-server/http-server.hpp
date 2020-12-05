#ifndef HTTTP_SERVER_NOSOOL
#define HTTP_SERVER_NOSKOOL

#include <boost/asio.hpp>

#include <boost/thread/thread.hpp>

#include <string>
#include <vector>
#include <functional>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;

class RequestsHandler
{
    std::string _method;
    std::string _url;
    std::string _version;
    std::string _body;
    std::string _httpVersion;
    std::string _contentType;
    std::string _responseFirstStr;
    std::string _responseBody;
    size_t _responseStatus;
    std::map<std::string, std::string> _requestHeaders;
    std::map<std::string, std::string> _responseHeaders;
    int isOurServer = 0;
    bool isResponseReady = false;
    size_t _number;

    void parseHeaders(std::istream& stream);
    std::string readResponseFile(const std::string& staticPath);
    std::string responseFormation(std::string body);
    std::string getExt(const std::string& st);
    void setMIMEType(const std::string& st);
    std::string encodeSStream(std::stringstream& stream);
    std::string gzipSStream(std::stringstream& stream);
    void logRequest();
    void setFirstHeader();
    std::string formationRequest();
    bool isOurServerFn(const std::string& header);
    void logRequestOur();

public:
    RequestsHandler() {};
    std::string getResponse(std::istream& stream, std::map<std::string, std::string> staticPath);
};

class ResponsesHandler
{
protected:
    ResponsesHandler() {}
    static ResponsesHandler* _objPtr;
    static std::mutex _mutex;
    std::map<size_t, std::string> _responses;
    std::map<size_t, std::function<void()>> _callbacks;

public:
    ResponsesHandler(ResponsesHandler &other) = delete;
    void operator=(const ResponsesHandler &) = delete;
    static ResponsesHandler* getInstance();

    std::string getResponse(size_t number);
    void setResponse(std::string response, size_t number);
    void setCallback(std::function<void()> fn, size_t number);
};

class Requester
{
protected:
    Requester():
    _ep(ip::address::from_string("127.0.0.1"), 8080),
    _sock(_requesterService) {
        _sock.connect(_ep);
        _requesterService.run();
    }
    static Requester* _objPtr;
    static std::mutex _requesterMutex;
    io_service _requesterService;
    ip::tcp::endpoint _ep;
    ip::tcp::socket _sock;

public:
    Requester(Requester &other) = delete;
    void operator=(const Requester &) = delete;
    static Requester* getInstance();

    void sendRequest(std::string body, std::function<void()> fn, size_t number);
};

class Session:  public std::enable_shared_from_this<Session>
{
public:
    Session(ip::tcp::socket socket)
        : _socket(std::move(socket))
        ,_strand(_socket.get_io_service()) {}

    void start(std::map<std::string, std::string> context);
private:
    ip::tcp::socket _socket;
    asio::streambuf _buffer;
    std::string _responseBuffer;
    RequestsHandler headers;
    boost::asio::io_service::strand _strand;
};

class HTTPServer
{
    std::string _loggerPath;
    std::string _loggerLevel;
    ip::tcp::acceptor _acceptor;
    ip::tcp::socket _socket;
    std::map<std::string, std::string> _context;
    void acceptAndRun();
    void initServer();
    void getConfFile();
    void initLogger();
    void setLoggerLevel();
public:
    HTTPServer(boost::asio::io_service& io_service, uint16_t port):
        _acceptor(io_service, ip::tcp::endpoint(ip::tcp::v4(), port)),
        _socket(io_service)
    {
        initServer();
        acceptAndRun();
    };
    ~HTTPServer() {};
};

#endif // !HTTTP_SERVER_NOSOOL
