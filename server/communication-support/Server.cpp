//
// Created by ndv on 6/23/19.
//

#include "Server.h"
#include <iostream>
Server::Server(const std::string &host, const std::string &service) :
        host(host), service(service) {
}

Server::~Server() {
}

void Server::run() {
    std::cout << "Server running.\n";
    Socket acceptorSocket;
    acceptorSocket.bindAndListen(host, service);
    RoomAcceptor roomAcceptor(roomManager, acceptorSocket);
    roomAcceptor.start();
    while (!_isDead) {
        std::this_thread::sleep_for (std::chrono::milliseconds(500));
        roomManager.removeFinishedGames();
    }
    roomAcceptor.stop();
    roomAcceptor.join();
}

void Server::stop() {
    _isDead = true;
}
