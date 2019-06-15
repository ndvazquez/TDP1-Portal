//
// Created by ndv on 6/13/19.
//

#ifndef PORTAL_STAGEMANAGER_H
#define PORTAL_STAGEMANAGER_H


#include "../common/UserEventQueue.h"
#include "Stage.h"
#include "../common/constants.h"
#include "../common/StageStatusQueue.h"

class StageManager {
    int playerCounter;
    UserEventQueue& userEventQueue;
    StageStatusQueue& stageStatusQueue;
    Stage stage;
    std::chrono::system_clock::time_point timeStamp;
    void handleEvent(UserEvent& userEvent, Chell* chell);
public:
    StageManager(UserEventQueue& eventQueue,
                StageStatusQueue& statusQueue,
                int stageWidth,
                int stageHeight);
    ~StageManager();
    // This is going to run on another thread.
    void run();
};


#endif //PORTAL_STAGEMANAGER_H
