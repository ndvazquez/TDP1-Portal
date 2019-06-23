//
// Created by cecix on 22/06/19.
//

#ifndef PORTAL_GAME_H
#define PORTAL_GAME_H


#include "../common/Protocol.h"

class Game {
private:
    Protocol& clientProtocol;
    Socket& clientSocket;
public:
    Game(Protocol& clientProtocol, Socket& clientSocket);
    void play();
};


#endif //PORTAL_GAME_H
