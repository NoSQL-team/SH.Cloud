#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>

#include <fstream>

#include "http-server.hpp"

#define NOT_FOUND "404"
#define OK "200"

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

void RequestsHandler::parseHeaders(std::istream& stream) {
    std::vector<std::string> splitVect;
    std::string headerBuffer;
    std::getline(stream, headerBuffer);
    boost::split(splitVect, headerBuffer, boost::is_any_of(" "));
    if (
        splitVect[0] == "GET" ||
        splitVect[0] == "POST" ||
        splitVect[0] == "PUT"
    ) {
        isOurServer = 1;
    } else if (std::all_of(headerBuffer.begin(), headerBuffer.end(), ::isdigit)) {
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
    std::string filePath = _url == "/" ? (staticPath + "/index.html") : (staticPath + _url);
    std::ifstream file(filePath);
    if(file.is_open()) {
        responseBody << file.rdbuf();
    } else {
        responseBody << NOT_FOUND;
    }
    file.close();
    return encodeSStream(responseBody);
}

void RequestsHandler::logRequest() {
    BOOST_LOG_TRIVIAL(info) << _method << " " << _url << " " << _responseFirstStr;
}

std::string RequestsHandler::getResponse(std::istream& stream, const std::string& staticPath)
{
    parseHeaders(stream);
    std::stringstream ssOut;
    _responseHeaders.insert({"Server", "linuxbox"});
    if(std::strncmp(_url.c_str(), "/api/", 5)) {
        std::string body = readResponseFile(staticPath);
        _responseHeaders.insert({"Content-Length", boost::lexical_cast<std::string>(body.length())});
        if (body == NOT_FOUND) {
            _responseFirstStr = "HTTP/1.1 404 NOT FOUND";
            logRequest();
            return responseFormation("");
        } else {
            _responseFirstStr = "HTTP/1.1 200 OK";
            logRequest();
            return responseFormation(body);
        }
    } else {
        ResponsesHandler* responsesHandler = ResponsesHandler::getInstance();
        return responseFormation("");
    }
    _responseFirstStr = "HTTP/1.1 500";
    return responseFormation("Some error");
}
