//
// Created by ndv on 6/16/19.
//

#include "ClientSender.h"
#include <iostream>

ClientSender::ClientSender(StageStatusQueue &stageQueue, Socket &socket) :
                            stageStatusQueue(stageQueue),
                            clientSocket(socket){
}

ClientSender::~ClientSender() {}

void ClientSender::run() {
    while (!_isDead) {
        try {
            // It should block here until there's something in the queue.
            std::string stageStatus = stageStatusQueue.pop();
            // Check for suicide pill and exit loop if it receives one.
            if (stageStatus.compare(THREAD_SUICIDE_PILL) == 0){
                _isDead = true;
                break;
            }
            int stageStatusSize = stageStatus.size();
            clientSocket.sendMessage(&stageStatusSize, REQUEST_LEN_SIZE);
            clientSocket.sendMessage(&stageStatus[0], stageStatusSize);
        } catch (std::runtime_error &e){
            // TODO: Implement a real exception.
            std::cout << "Force shutdown, expected behaviour." << std::endl;
            _isDead = true;
        } catch (...) {
            _isDead = true;
            std::cout << "Aborting Sender execution." << std::endl;
            return;
        }
    }
}

void ClientSender::stop() {
    _isDead = true;
}
