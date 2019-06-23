//
// Created by cecix on 21/06/19.
//

#ifndef PORTAL_PROTOCOL_H
#define PORTAL_PROTOCOL_H


#include "Socket.h"

class Protocol {
private:
    Socket& socket;
public:
    explicit Protocol(Socket& socket);
    std::string receiveMessage();
    void sendMessage(std::string& message);
};

#endif //PORTAL_PROTOCOL_H
