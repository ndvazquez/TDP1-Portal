//
// Created by ndv on 6/16/19.
//

#include "ClientReceiver.h"

ClientReceiver::ClientReceiver(UserEventQueue &eventQueue, Socket &socket) :
                                userEventQueue(eventQueue),
                                clientSocket(socket){
}

ClientReceiver::~ClientReceiver() {}

void ClientReceiver::run() {
    while (!_isDead) {
        try {
            uint32_t string_size;
            // It blocks here.
            clientSocket.receiveMessage(&string_size, REQUEST_LEN_SIZE);
            std::string eventString(string_size, '\0');
            // It blocks here.
            clientSocket.receiveMessage(&eventString[0], string_size);
            nlohmann::json eventJson = nlohmann::json::parse(eventString);
            UserEvent userEvent(eventJson);
            // Could block here too.
            userEventQueue.push(userEvent);
        } catch (...) {
            _isDead = true;
        }
    }
}

void ClientReceiver::stop() {
    _isDead = true;
}
