#include "auth-server.hpp"

std::string RequestsHandler::getResponse(std::istream& stream)
{
    std::stringstream ssOut;
    ssOut << "12\n" << "\n" << "{\"token\": \"123ewfewsags.esfsef.sefsefsefsef\"}";

    return ssOut.str();
}
