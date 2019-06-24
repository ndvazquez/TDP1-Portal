//
// Created by cecix on 22/06/19.
//

#ifndef PORTAL_GAME_H
#define PORTAL_GAME_H


#include "../common/Protocol.h"
#include "../common/Window.h"

class Game {
private:
    Protocol& clientProtocol;
    Socket& clientSocket;
    Window& window;
public:
    Game(Protocol& clientProtocol, Socket& clientSocket, Window& window);
    bool play(std::string& idChell);
};


#endif //PORTAL_GAME_H
