//
// Created by ndv on 6/16/19.
//

#include <iostream>
#include "ClientHandler.h"
#include <chrono>

ClientHandler::ClientHandler(Socket &socket,
        UserEventQueue &eventQueue,
        StageStatusQueue &stageQueue) :
        peerSocket(std::move(socket)),
        userEventQueue(eventQueue),
        stageStatusQueue(stageQueue),
        clientSender(ClientSender(stageStatusQueue, peerSocket)),
        clientReceiver(ClientReceiver(userEventQueue, peerSocket)){
}

ClientHandler::~ClientHandler() {
}

void ClientHandler::run() {
    clientSender.start();
    clientReceiver.start();
    bool quit = false;
    while (!quit || !_isDead) {
        std::this_thread::sleep_for (std::chrono::seconds(1));
        if (clientSender.isDead() || clientReceiver.isDead()) {
            quit = true;
            _isDead = true;
        }
    }
}

void ClientHandler::stop() {
    // This should force stop each child.
    peerSocket.shutdownAndClose();
    // Stop each child.
    clientSender.stop();
    clientReceiver.stop();
    clientSender.join();
    clientReceiver.join();
    _isDead = true;
}
