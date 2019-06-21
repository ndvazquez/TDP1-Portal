//
// Created by ndv on 6/20/19.
//

#ifndef PORTAL_ROOMWORKER_H
#define PORTAL_ROOMWORKER_H


#include "../../common/Thread.h"
#include "../../common/Socket.h"
#include "RoomManager.h"

class RoomWorker : public Thread{
    RoomManager& roomManager;
    Socket clientSocket;
    Protocol clientProtocol;
    bool handleGameCreation(nlohmann::json& actionData);
    bool handleJoinGame(nlohmann::json& actionData);
public:
    RoomWorker(Socket& socket, RoomManager& roomManager);
    ~RoomWorker();
    void run();
    void stop();
};


#endif //PORTAL_ROOMWORKER_H
