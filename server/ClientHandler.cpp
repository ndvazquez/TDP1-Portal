//
// Created by ndv on 6/16/19.
//

#include "ClientHandler.h"

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
    // If the thread dies, it has to take care of the childs resources.
    peerSocket.shutdownAndClose();
    clientSender.join();
    clientReceiver.join();
}

void ClientHandler::run() {
    clientSender.start();
    clientReceiver.start();
    bool quit = false;
    while (!quit || !_isDead) {
        if (clientSender.isDead() || clientReceiver.isDead()) {
            quit = true;
        }
    }
    peerSocket.shutdownAndClose();
    // Stop each child.
    clientSender.stop();
    clientReceiver.stop();
    _isDead = true;
}

void ClientHandler::stop() {
    // This should force stop each child.
    peerSocket.shutdownAndClose();
    _isDead = true;
}
