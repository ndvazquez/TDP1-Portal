//
// Created by ndv on 6/17/19.
//

#ifndef PORTAL_STAGESTATUSRECEIVER_H
#define PORTAL_STAGESTATUSRECEIVER_H


#include "../common/Thread.h"
#include "../common/StageStatusQueue.h"
#include "../common/Socket.h"
#include "../json/json.hpp"
#include "../common/constants.h"

class StageStatusReceiver : public Thread {
    Socket& clientSocket;
    StageStatusQueue& stageStatusQueue;
public:
    StageStatusReceiver(Socket& socket,
            StageStatusQueue& statusQueue);
    ~StageStatusReceiver();
    void run();
    void stop();
};


#endif //PORTAL_STAGESTATUSRECEIVER_H
