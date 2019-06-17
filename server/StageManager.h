//
// Created by ndv on 6/13/19.
//

#ifndef PORTAL_STAGEMANAGER_H
#define PORTAL_STAGEMANAGER_H


#include "../common/UserEventQueue.h"
#include "Stage.h"
#include "../common/constants.h"
#include "../common/StageStatusQueue.h"
#include "ClientHandler.h"
#include <unordered_map>
#include <string>

class StageManager {
    int playerCounter;
    UserEventQueue userEventQueue;
    Stage stage;
    std::unordered_map<std::string, ClientHandler*> clients;
    std::unordered_map<std::string, StageStatusQueue*> clientQueues;

    std::chrono::system_clock::time_point timeStamp;
    void handleEvent(UserEvent& userEvent, Chell* chell);
public:
    StageManager(int stageWidth,
                int stageHeight);
    ~StageManager();
    // This is going to run on another thread.
    void run();
    void addPlayer(Socket& socket);
};


#endif //PORTAL_STAGEMANAGER_H
