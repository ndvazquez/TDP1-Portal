//
// Created by ndv on 6/12/19.
//

#ifndef PORTAL_USEREVENTHANDLER_H
#define PORTAL_USEREVENTHANDLER_H

#include "../../common/constants.h"
#include "views/Camera.h"
#include "../../common/UserEventQueue.h"
#include "audio/SoundCodeQueue.h"
#include "../../common/Thread.h"
#include "../../common/Window.h"


class UserEventHandler : public Thread {
    const float mtpFactorInv = 1.0f / MTP_FACTOR;
    const Camera& camera;
    UserEventQueue& userEventQueue;
    const std::string& userId;
    int levelHeight;
    SoundCodeQueue& soundCodeQueue;
    Window& gameWindow;
    void handleEvent(SDL_Event& event);

public:
    UserEventHandler(const Camera& camera,
            UserEventQueue& userEventQueue,
            const std::string& userId,
            int levelHeight,
            SoundCodeQueue& soundCodeQueue,
            Window& gameWindow);
    ~UserEventHandler();
    void run();
    void stop();
};


#endif //PORTAL_USEREVENTHANDLER_H
