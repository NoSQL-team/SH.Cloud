#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <cstdlib>


#include "http-server.hpp"

namespace logging = boost::log;
namespace keywords = boost::log::keywords;

void HTTPServer::getConfFile() {
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("noskoolHTTP.ini", pt);
    try
    {
        _port = pt.get<uint16_t>("server.port");
        _loggerPath = pt.get<std::string>("logger.path");
        _loggerLevel = pt.get<std::string>("logger.level");
        _staticPath = pt.get<std::string>("server.static_path");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
}

void HTTPServer::setLoggerLevel() {
    auto level = logging::trivial::warning;
    if (_loggerLevel == "trace") {
        level = logging::trivial::trace;
    } else if (_loggerLevel == "debug") {
        level = logging::trivial::debug;
    } else if (_loggerLevel == "info") {
        level = logging::trivial::info;
    } else if (_loggerLevel == "error") {
        level = logging::trivial::error;
    } else if (_loggerLevel == "fatal") {
        level = logging::trivial::fatal;
    }
    logging::core::get()->set_filter(
        logging::trivial::severity >= level
    );
}

void HTTPServer::initLogger() {
    setLoggerLevel();
}

void HTTPServer::initServer() {
    getConfFile();
    initLogger();
}

void HTTPServer::acceptAndRun(ip::tcp::acceptor& acceptor, io_service& io_service)
{
    std::shared_ptr<Session> sesh = std::make_shared<Session>(io_service);

    acceptor.async_accept(
        sesh->socket,
        [sesh, &acceptor, &io_service, this](const error_code& accept_error)
        {
            acceptAndRun(acceptor, io_service);
            if(!accept_error) {
                Session::handleRequest(sesh, _staticPath);
            }
        }
    );
}

void HTTPServer::run()
{
    initServer();
    io_service io_service;
    ip::tcp::endpoint endpoint{ip::tcp::v4(), _port};
    ip::tcp::acceptor acceptor{io_service, endpoint};
    
    acceptor.listen();
    acceptAndRun(acceptor, io_service);
    
    io_service.run();
}