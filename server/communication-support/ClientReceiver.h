//
// Created by ndv on 6/16/19.
//

#ifndef PORTAL_CLIENTRECEIVER_H
#define PORTAL_CLIENTRECEIVER_H


#include "../common/Thread.h"
#include "../common/UserEventQueue.h"
#include "../common/UserEvent.h"
#include "../common/Socket.h"
#include "../json/json.hpp"
#include "../common/constants.h"
#include "../../common/Protocol.h"

class ClientReceiver : public Thread {
    UserEventQueue& userEventQueue;
    //Socket& clientSocket;
    Protocol clientProtocol;

public:
    ClientReceiver(UserEventQueue& eventQueue,
            Socket& socket);
    ~ClientReceiver();
    void run();
    void stop();
};


#endif //PORTAL_CLIENTRECEIVER_H
