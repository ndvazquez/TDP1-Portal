//
// Created by ndv on 6/16/19.
//

#include "ClientReceiver.h"
#include <iostream>

ClientReceiver::ClientReceiver(UserEventQueue &eventQueue, Socket &socket) :
                                userEventQueue(eventQueue),
                                clientProtocol(socket) {
}

ClientReceiver::~ClientReceiver() {}

void ClientReceiver::run() {
    while (!_isDead) {
        try {
            std::string eventString = clientProtocol.receiveMessage();
            nlohmann::json eventJson = nlohmann::json::parse(eventString);
            UserEvent userEvent(eventJson);
            // Could block here too.
            userEventQueue.push(userEvent);
        } catch (const std::exception &e) {
            std::cout << "Force shutdown, expected behaviour." << std::endl;
            _isDead = true;
        } catch(...) {
            _isDead = true;
            std::cout << "Aborting Receiver execution." << std::endl;
            return;
        }
    }
}

void ClientReceiver::stop() {
    _isDead = true;
}
