//
// Created by ndv on 6/16/19.
//

#include "ClientSender.h"

ClientSender::ClientSender(StageStatusQueue &stageQueue, Socket &socket) :
                            stageStatusQueue(stageQueue),
                            clientSocket(socket){
}

ClientSender::~ClientSender() {}

void ClientSender::run() {
    while (!_isDead){
        try {
            // It should block here until there's something in the queue.
            std::string stageStatus = stageStatusQueue.pop();
            // Check for suicide pill and exit loop if it receives one.
            if (stageStatus.compare(THREAD_SUICIDE_PILL) == 0){
                _isDead = true;
                break;
            }
            int stageStatusSize = stageStatus.length();
            clientSocket.sendMessage(stageStatus.c_str(), stageStatusSize);
        } catch (...){
            // TODO: Implement a real exception.
            _isDead = true;
        }
    }
}

void ClientSender::stop() {
    _isDead = true;
}
