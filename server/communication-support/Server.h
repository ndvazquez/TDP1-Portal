//
// Created by ndv on 6/23/19.
//

#ifndef PORTAL_SERVER_H
#define PORTAL_SERVER_H


#include "../../common/Thread.h"
#include <string>
#include "../common/Socket.h"
#include "communication-support/StageManager.h"
#include <communication-support/RoomManager.h>
#include <communication-support/RoomAcceptor.h>

class Server : public Thread {
    const std::string host;
    const std::string service;
    RoomManager roomManager;
public:
    Server(const std::string& host,
            const std::string& service);
    ~Server();
    void run();
    void stop();
};


#endif //PORTAL_SERVER_H
