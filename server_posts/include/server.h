//
// Created by steve on 15.12.2020.
//

#ifndef MAIN_TP_SERVER_H
#define MAIN_TP_SERVER_H

#include "../include/handlers.h"
#include "../include/types.h"
#include "../include/session.h"



class TCPServer {
public:

    TCPServer(io::io_context& io_context, std::uint16_t port)
            : io_context(io_context)
            , acceptor  (io_context, tcp::endpoint(tcp::v4(), port)),
              hand() {

        accept();
    }

    void add_endpoint();

private:

    void accept();

    io::io_context& io_context;
    tcp::acceptor acceptor;
    std::optional<tcp::socket> socket;
public:
    std::map<std::string, dispatcher_entry> dispatcher;
    std::map<std::string, dispatcher_entry_with_body> dispatcher_with_body;
    Handlers hand;
};

#endif //MAIN_TP_SERVER_H
