#include <boost/algorithm/string.hpp>

#include <boost/lexical_cast.hpp>

#include <boost/log/trivial.hpp>

#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>

#include <fstream>
#include <chrono>
#include <thread>

#include "http-server.hpp"

#define NOT_FOUND "HTTP/1.1 404 Not Found"
#define OK "HTTP/1.1 200 OK"
#define INTERNAL_SERVER_ERROR "HTTP/1.1 500 Internal Server Error"
#define BAD_REQUEST "HTTP/1.1 400 Bad Request"
#define METHOD_NOT_ALLOWED "HTTP/1.1 405 Method Not Allowed"

extern size_t number;
extern std::mutex ResponsesHandler::_mutex;
extern std::mutex Requester::_requesterMutex;

std::string RequestsHandler::getExt(const std::string& st) {
    size_t pos = st.rfind('.');
    if (pos <= 0) return "";
    return st.substr(pos+1, std::string::npos);
}

void RequestsHandler::setMIMEType(const std::string& st) {
    std::string ext = getExt(st);
    if (st == "/") {
        _responseHeaders.insert({"Content-Type", "text/html; charset=UTF-8"});
    } else if (ext == "js") {
        _responseHeaders.insert({"Content-Type", "application/javascript; charset=UTF-8"});
    } else if(ext == "css") {
        _responseHeaders.insert({"Content-Type", "text/css; charset=UTF-8"});
    } else if (ext == "map") {
        _responseHeaders.insert({"Content-Type", "application/json; charset=UTF-8"});
    } else if (ext == "png") {
        _responseHeaders.insert({"Content-Type", "image/png"});
    } else if (ext == "jpeg" || ext == "jpg") {
        _responseHeaders.insert({"Content-Type", "image/jpeg"});
    } else if (ext == "gif") {
        _responseHeaders.insert({"Content-Type", "image/gif"});
    }
    else {
        return;
    }
}

bool RequestsHandler::isOurServerFn(const std::string& header) {
    bool isOur = true;
    for (size_t i = 0; i < header.size() - 1; i++) {
        if(!isdigit(header[i])) {
            isOur = false;
        }
    }
    _number = isOur ? lexical_cast<size_t>(header) : 0;
    isOurServer = (isOur ? 1 : 10);
    return isOur;
}

void RequestsHandler::parseHeaders(std::istream& stream) {
    std::vector<std::string> splitVect;
    std::string headerBuffer;
    std::getline(stream, headerBuffer);
    boost::split(splitVect, headerBuffer, boost::is_any_of(" "));
    if (isOurServerFn(headerBuffer)) {
        while (std::getline(stream, headerBuffer)) {
            _body += headerBuffer + '\n';
        }
        return;
    } else if (
        splitVect[0] == "GET" ||
        splitVect[0] == "POST" ||
        splitVect[0] == "PUT"
    ) {
        isOurServer = 0;
    } else { 
        isOurServer = -1;
        return;
    }
    _method = splitVect[0];
    _url = splitVect[1];
    _httpVersion = splitVect[2];
    splitVect.clear();
    while(std::getline(stream, headerBuffer)) {
        if (headerBuffer == "\r") {
            break;
        } else {
            boost::split(splitVect, headerBuffer, boost::is_any_of(":"));
            _requestHeaders.insert({splitVect[0], splitVect[1]});
            splitVect.clear();
        }
    }
    if (_requestHeaders.find("Content-Length") != _requestHeaders.end()) {
        while (std::getline(stream, headerBuffer)) {
            _body += headerBuffer + '\n';
        }
    }
    setMIMEType(_url);
}

std::string RequestsHandler::gzipSStream(std::stringstream& stream) {
    std::stringstream buffer;
    boost::iostreams::filtering_streambuf< boost::iostreams::input> in;
    in.push(boost::iostreams::gzip_compressor());
    in.push(stream);
    boost::iostreams::copy(in, buffer);
    return buffer.str();
}

std::string RequestsHandler::encodeSStream(std::stringstream& stream) {
    if (_requestHeaders.find("Accept-Encoding") != _requestHeaders.end()) {
        if (_requestHeaders.find("Accept-Encoding")->second.find("gzip") != std::string::npos) {
            _responseHeaders.insert({"content-encoding", "gzip"});
            return gzipSStream(stream);
        } else {
            return stream.str();
        }
    }
    return stream.str();
}

std::string RequestsHandler::responseFormation(std::string body = "") {
    std::stringstream buffer;
    buffer << _responseFirstStr << std::endl;
    for (const auto& [header, value] : _responseHeaders) {
        buffer << header << ": " << value << std::endl;
    }
    buffer << std::endl << boost::lexical_cast<std::string>(body);
    return buffer.str();
}

std::string RequestsHandler::readResponseFile(const std::string& staticPath) {
    std::stringstream responseBody;
    std::string filePath;
    if (
        _url == "/" ||
        _url == "/moment" ||
        _url == "/login" ||
        _url == "/profile"
    ) {
        filePath = staticPath + "/index.html";
    } else {
        filePath = staticPath + _url;
    }
    std::ifstream file(filePath);
    if(file.is_open()) {
        responseBody << file.rdbuf();
        _responseStatus = 200;
    } else {
        responseBody << "";
        _responseStatus = 404;
    }
    file.close();
    return encodeSStream(responseBody);
}

void RequestsHandler::logRequest() {
    BOOST_LOG_TRIVIAL(info) << _method << " " << _url << " " << _responseFirstStr;
}

void RequestsHandler::logRequestOur() {
    BOOST_LOG_TRIVIAL(info) << "Our server: " << _number;
}

void RequestsHandler::setFirstHeader() {
    switch (_responseStatus)
    {
    case 200:
        _responseFirstStr = OK;
        break;
    case 400:
        _responseFirstStr = BAD_REQUEST;
        break;
    case 404:
        _responseFirstStr = NOT_FOUND;
        break;
    case 405: 
        _responseFirstStr = METHOD_NOT_ALLOWED;
        break;
    default:
        _responseFirstStr = INTERNAL_SERVER_ERROR;
    }
}

std::string RequestsHandler::formationRequest() {
    std::stringstream buffer;
    number++;
    buffer 
        << number << "\n"
        << _url << "\n"
        << "\n"
        << _body << "\r";
    return buffer.str();    
}

std::string RequestsHandler::getResponse(std::istream& stream, std::map<std::string, std::string> context)
{
    parseHeaders(stream);
    _responseHeaders.insert({"Server", "linuxbox"});
    if (isOurServer == -1) {
        _responseStatus = 405;
        _responseBody = "Method not allowed";
    } else if (isOurServer == 1) {
        ResponsesHandler* responsesHandler = ResponsesHandler::getInstance();
        responsesHandler->setResponse(_body, _number);
    } else if (isOurServer == 0) {
        std::stringstream ssOut;
        if(std::strncmp(_url.c_str(), "/api/", 5)) {
            isOurServer = 2;
            _responseBody = readResponseFile(context["staticPath"]);
        } else {
            Requester* requester = Requester::getInstance();
            requester->sendRequest(formationRequest(), [this](){ isResponseReady = true; }, number + 1);
            _number = number;
            while (!isResponseReady) {
                std::this_thread::sleep_for(std::chrono::microseconds(100));
            }
            ResponsesHandler* responsesHandler = ResponsesHandler::getInstance();
            _responseBody = responsesHandler->getResponse(_number);
            _responseHeaders.insert({"Content-Type", "application/json; charset=UTF-8"});
            _responseStatus = 200;
        }
    }
    setFirstHeader();
    if (!(isOurServer == 1)) {
        _responseHeaders.insert({
            "Content-Length", boost::lexical_cast<std::string>(_responseBody.length())
        });
        logRequest();
    }  else {
        logRequestOur();
    }
    return (isOurServer == 1) ? "our" : responseFormation(_responseBody);
}
