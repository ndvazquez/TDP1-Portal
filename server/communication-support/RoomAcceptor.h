//
// Created by ndv on 6/20/19.
//

#ifndef PORTAL_ROOMACCEPTOR_H
#define PORTAL_ROOMACCEPTOR_H

#include <list>
#include "../../common/Thread.h"
#include "RoomWorker.h"
#include "../../common/Socket.h"
#include "RoomManager.h"

class RoomAcceptor : public Thread{
    std::list<RoomWorker*> workers;
    RoomManager& roomManager;
    bool keepRunning;
    Socket acceptorSocket;
public:
    RoomAcceptor(RoomManager& roomManager,
            Socket& socket);
    ~RoomAcceptor();
    void run();
    void stop();
};


#endif //PORTAL_ROOMACCEPTOR_H
