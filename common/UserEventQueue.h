//
// Created by ndv on 6/12/19.
//

#ifndef PORTAL_USEREVENTQUEUE_H
#define PORTAL_USEREVENTQUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include "UserEvent.h"

class UserEventQueue {
    std::condition_variable _cv;
    std::mutex _mtx;
    std::queue<UserEvent> internalQueue;

public:
    UserEventQueue();
    ~UserEventQueue();
    void push(UserEvent& newUserEvent);
    UserEvent pop();
    bool empty();
};

#endif //PORTAL_USEREVENTQUEUE_H
