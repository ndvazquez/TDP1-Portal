//
// Created by ndv on 6/16/19.
//

#include "ClientReceiver.h"
#include <iostream>

ClientReceiver::ClientReceiver(UserEventQueue &eventQueue, Socket &socket) :
                                userEventQueue(eventQueue),
                                //clientSocket(socket){
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
        } catch (std::runtime_error &e) { //TODO: it should be exception afterwards
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
