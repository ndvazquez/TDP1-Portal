//
// Created by cecix on 22/06/19.
//

#ifndef PORTAL_DRAWER_H
#define PORTAL_DRAWER_H

#include "../common/Protocol.h"
#include "../common/Window.h"

class Drawer {
private:
    Protocol& clientProtocol;
    Socket& clientSocket;
    Window& newWindow;
public:
    Drawer(Protocol& clientProtocol, Socket& clientSocket, Window& window);
    void draw(std::string& idChell);
};

#endif //PORTAL_DRAWER_H
