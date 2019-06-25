//
// Created by cecix on 22/06/19.
//

#ifndef PORTAL_DRAWER_H
#define PORTAL_DRAWER_H

#include "../common/Protocol.h"
#include <audio/SoundCodeQueue.h>
#include <audio/AudioSystem.h>
#include <communication-support/UserEventHandler.h>
#include <communication-support/EventSender.h>
#include <communication-support/StageStatusReceiver.h>
#include "../common/Window.h"
#include "../common/Sprite.h"
#include "views/StageView.h"
#include "views/Camera.h"
#include "../common/UserEventQueue.h"
#include "../common/StageStatusQueue.h"
#include "views/ViewManager.h"
#include <yaml-cpp/node/node.h>
#include "../common/constants.h"

#define CLIENT_TEXTURE_CONFIG_FILE "config/textures.yaml"

class Drawer {
private:
    Protocol& clientProtocol;
    Socket& clientSocket;
    Window& newWindow;
    int mtpFactor;
public:
    Drawer(Protocol& clientProtocol, Socket& clientSocket, Window& window,
            int mtpFactor);
    void draw(std::string& idChell);
};

#endif //PORTAL_DRAWER_H
