//
// Created by ndv on 6/12/19.
//

#ifndef PORTAL_USEREVENTHANDLER_H
#define PORTAL_USEREVENTHANDLER_H

#include "../common/constants.h"
#include "Camera.h"
#include "../common/UserEventQueue.h"
#include "SoundCodeQueue.h"
#include "../common/Thread.h"

#define MTP_FACTOR_INV 0.01f

class UserEventHandler : public Thread {
    const Camera& camera;
    UserEventQueue& userEventQueue;
    const std::string& userId;
    int levelHeight;
    SoundCodeQueue& soundCodeQueue;
    void handleEvent(SDL_Event& event);

public:
    UserEventHandler(const Camera& camera,
            UserEventQueue& userEventQueue,
            const std::string& userId,
            int levelHeight,
            SoundCodeQueue& soundCodeQueue);
    ~UserEventHandler();
    void run();
    void stop();
};


#endif //PORTAL_USEREVENTHANDLER_H
