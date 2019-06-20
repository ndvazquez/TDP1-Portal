//
// Created by cecix on 12/05/19.
//

#include <string>
#include <unordered_map>
#include "entities/Button.h"
#include "entities/Gate.h"
#include "stage-support/Stage.h"
#include "../common/Socket.h"
#include "stage-support/StageManager.h"
#include <iostream>
#include <communication-support/RoomManager.h>
#include <communication-support/RoomAcceptor.h>

void testRunServer() {
    std::string host = "localhost";
    std::string service = "8000";
    char c = '*';
    Socket acceptorSocket;
    acceptorSocket.bindAndListen(host, service);
    RoomManager roomManager;
    RoomAcceptor roomAcceptor(roomManager, acceptorSocket);
    roomAcceptor.start();
    while (c != 'q'){
        std::cin.get(c);
    }
    roomAcceptor.stop();
    roomAcceptor.join();
}
int main(int argc, char* argv[]) {
    testRunServer();
    return 0;
}