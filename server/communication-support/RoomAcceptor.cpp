//
// Created by ndv on 6/20/19.
//

#include "RoomAcceptor.h"

RoomAcceptor::RoomAcceptor(RoomManager &roomManager, Socket &socket) :
                    roomManager(roomManager),
                    acceptorSocket(std::move(socket)){
}

RoomAcceptor::~RoomAcceptor() {
    acceptorSocket.shutdownAndClose();
}

void RoomAcceptor::run() {
    while (keepRunning){
        Socket peerSocket = acceptorSocket.acceptPeer();
        if (!peerSocket.isValid()) continue;
        workers.push_front(new RoomWorker(peerSocket,
                                       roomManager));
        workers.front()->start();
        auto it = workers.begin();
        while (it != workers.end()){
            if ((*it)->isDead()){
                (*it)->join();
                delete *it;
                it = workers.erase(it);
            } else{
                ++it;
            }
        }
    }
    for (auto it = workers.begin(); it != workers.end(); ++it){
        (*it)->stop();
        (*it)->join();
        delete *it;
    }
}

void RoomAcceptor::stop() {
    keepRunning = false;
    acceptorSocket.shutdownAndClose();
}