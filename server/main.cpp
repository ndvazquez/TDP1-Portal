//
// Created by cecix on 12/05/19.
//

#include <string>
#include <unordered_map>
#include "Button.h"
#include "Gate.h"
#include "Stage.h"
#include "../common/Socket.h"
#include "StageManager.h"
#include <iostream>

void testRunServer() {
    std::string host = "localhost";
    std::string service = "8000";
    int stageWidth = 40;
    int stageHeight = 20;
    int chellPosX = 4;
    int chellPosY = 1;
    Socket acceptorSocket;
    acceptorSocket.bindAndListen(host, service);
    Socket peerSocket1 = acceptorSocket.acceptPeer();
    Socket peerSocket2 = acceptorSocket.acceptPeer();
    StageManager stageManager(stageWidth, stageHeight);
    stageManager.addPlayer(peerSocket1, chellPosX, chellPosY);
    stageManager.addPlayer(peerSocket2, chellPosX + 20, chellPosY);
    stageManager.run();
    peerSocket1.shutdownAndClose();
    peerSocket2.shutdownAndClose();
    acceptorSocket.shutdownAndClose();
}
int main(int argc, char* argv[]) {
    testRunServer();
    return 0;
}
