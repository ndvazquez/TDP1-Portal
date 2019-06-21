//
// Created by ndv on 6/17/19.
//

#ifndef PORTAL_EVENTSENDER_H
#define PORTAL_EVENTSENDER_H


#include "../../common/Thread.h"
#include "../../common/Socket.h"
#include "../../json/json.hpp"
#include "../../common/constants.h"
#include "../../common/UserEventQueue.h"
#include "../../common/UserEvent.h"
#include "../../common/Protocol.h"

class EventSender : public Thread{
    Protocol clientProtocol;
    UserEventQueue& userEventQueue;
public:
    EventSender(Socket& socket,
            UserEventQueue& eventQueue);
    ~EventSender();
    void run();
    void stop();
};


#endif //PORTAL_EVENTSENDER_H
