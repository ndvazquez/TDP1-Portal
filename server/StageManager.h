//
// Created by ndv on 6/13/19.
//

#ifndef PORTAL_STAGEMANAGER_H
#define PORTAL_STAGEMANAGER_H


#include "../common/UserEventQueue.h"
#include "Stage.h"
#include "../common/constants.h"

class StageManager {
    Stage& stage;
    UserEventQueue& userEventQueue;
    std::chrono::system_clock::time_point timeStamp;
    void handleEvent(UserEvent& userEvent, Chell* chell);
public:
    StageManager(Stage& stage, UserEventQueue& queue);
    ~StageManager();
    // This is going to run on another thread.
    void run();
};


#endif //PORTAL_STAGEMANAGER_H
