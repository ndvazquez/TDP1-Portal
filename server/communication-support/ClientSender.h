//
// Created by ndv on 6/16/19.
//

#ifndef PORTAL_CLIENTSENDER_H
#define PORTAL_CLIENTSENDER_H

#include "../common/Thread.h"
#include "../common/StageStatusQueue.h"
#include "../common/Socket.h"
#include "../json/json.hpp"
#include "../common/constants.h"
#include "../../common/Protocol.h"

class ClientSender : public Thread {
    StageStatusQueue& stageStatusQueue;
    Protocol clientProtocol;

public:
    ClientSender(StageStatusQueue& stageQueue,
            Socket& socket);
    ~ClientSender();
    void run();
    void stop();
};

#endif //PORTAL_CLIENTSENDER_H
