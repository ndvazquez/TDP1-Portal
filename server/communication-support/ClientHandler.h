//
// Created by ndv on 6/16/19.
//

#ifndef PORTAL_CLIENTHANDLER_H
#define PORTAL_CLIENTHANDLER_H

#include "../../common/Thread.h"
#include "../../common/UserEventQueue.h"
#include "../../common/StageStatusQueue.h"
#include "../../common/Socket.h"
#include "ClientSender.h"
#include "ClientReceiver.h"

class ClientHandler : public Thread {
    UserEventQueue& userEventQueue;
    StageStatusQueue& stageStatusQueue;
    Socket peerSocket;
    ClientSender clientSender;
    ClientReceiver clientReceiver;
public:
    ClientHandler(Socket& socket,
            UserEventQueue& eventQueue,
            StageStatusQueue& stageQueue);
    ~ClientHandler();
    void run();
    void stop();
};


#endif //PORTAL_CLIENTHANDLER_H
