//
// Created by ndv on 6/12/19.
//

#include "UserEventQueue.h"

UserEventQueue::UserEventQueue() {
}

UserEventQueue::~UserEventQueue() {}

void UserEventQueue::push(UserEvent &newUserEvent) {
    std::unique_lock<std::mutex> _lock(_mtx);
    internalQueue.push(newUserEvent);
    _cv.notify_one();
}

UserEvent UserEventQueue::pop() {
    std::unique_lock<std::mutex> _lock(_mtx);
    while (internalQueue.empty()){
        _cv.wait(_lock);
    }
    UserEvent userEvent = internalQueue.front();
    internalQueue.pop();
    return userEvent;
}

bool UserEventQueue::empty() {
    std::unique_lock<std::mutex> _lock(_mtx);
    return internalQueue.empty();
}