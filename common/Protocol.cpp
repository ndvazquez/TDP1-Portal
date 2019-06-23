//
// Created by cecix on 21/06/19.
//

#include "Protocol.h"
#include "constants.h"
#include <arpa/inet.h>
#include <iostream>

Protocol::Protocol(Socket &socket):
    socket(socket) {
}

std::string Protocol::receiveMessage() {
    uint32_t stringSize;
    socket.receiveMessage(&stringSize, REQUEST_LEN_SIZE);
    std::cout << "Received size in network endian: " << stringSize << std::endl;
    stringSize = ntohl(stringSize);
    std::cout << "Received size in host endian: " << stringSize << std::endl;
    std::string eventString(stringSize, '\0');
    socket.receiveMessage(&eventString[0], stringSize);
    return eventString;
}

void Protocol::sendMessage(std::string& message) {
    uint32_t size = htonl(message.size());
    socket.sendMessage(&size, REQUEST_LEN_SIZE);
    socket.sendMessage(&message[0], message.size());
}
