//
// Created by ndv on 6/13/19.
//

#ifndef PORTAL_STAGEMANAGER_H
#define PORTAL_STAGEMANAGER_H


#include "../../common/UserEventQueue.h"
#include "Stage.h"
#include "../../common/constants.h"
#include "../../common/StageStatusQueue.h"
#include "communication-support/ClientHandler.h"
#include "YamlParser.h"
#include <unordered_map>
#include <string>

class StageManager : public Thread {
    int playerCounter;
    int maxPlayers;
    UserEventQueue userEventQueue;
    Stage stage;
    std::unordered_map<std::string, ClientHandler*> clients;
    std::unordered_map<std::string, StageStatusQueue*> clientQueues;
    // This maps a player ID to a Chell ID.
    std::unordered_map<std::string, std::string> players;
    YamlParser parser;

    std::chrono::system_clock::time_point timeStamp;
    void handleEvent(UserEvent& userEvent, Chell* chell);
public:
    StageManager(float stageWidth,
                float stageHeight, std::string& levelPath,
                int maxPlayers);
    ~StageManager();
    // This is going to run on another thread.
    void run();
    void stop();
    bool addPlayer(Socket& socket,
            const std::string& playerID);
    bool isFull();
};


#endif //PORTAL_STAGEMANAGER_H
