//
// Created by ndv on 6/17/19.
//

#include "StageStatusReceiver.h"

StageStatusReceiver::StageStatusReceiver(Socket &socket,
        StageStatusQueue &statusQueue) :
        clientSocket(socket),
        stageStatusQueue(statusQueue) {
}

StageStatusReceiver::~StageStatusReceiver() {}

void StageStatusReceiver::run() {
    while (!_isDead) {
        try {
            uint32_t string_size;
            clientSocket.receiveMessage(&string_size, REQUEST_LEN_SIZE);
            std::string stageStatusString(string_size, '\0');
            clientSocket.receiveMessage(&stageStatusString[0], string_size);
            bool jsonIsValid = nlohmann::json::accept(stageStatusString);
            if (!jsonIsValid) {
                // This is a bad idea, but we'll quit
                // if we receive an invalid json.
                _isDead = true;
                continue;
            }
            stageStatusQueue.push(stageStatusString);
        } catch (std::runtime_error &e) {
            //TODO: Implement a real exception for a socket blowing up.
            _isDead = true;
        } catch(...) {
            _isDead = true;
            return;
        }
    }
}

void StageStatusReceiver::stop() {
    _isDead = true;
}