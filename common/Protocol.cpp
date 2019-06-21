//
// Created by cecix on 21/06/19.
//

#include "Protocol.h"
#include "constants.h"

Protocol::Protocol(Socket &socket):
    socket(socket) {
}

std::string Protocol::receiveMessage() {
    uint32_t string_size;
    // It blocks here
    socket.receiveMessage(&string_size, REQUEST_LEN_SIZE);
    std::string eventString(string_size, '\0');
    // It blocks here.
    socket.receiveMessage(&eventString[0], string_size);
    return eventString;
}

void Protocol::sendMessage(std::string& message) {
    int size = message.size();
    socket.sendMessage(&size, REQUEST_LEN_SIZE);
    socket.sendMessage(&message[0], size);
}
