//
// Created by ndv on 6/2/19.
//

#include "SoundCodeQueue.h"

SoundCodeQueue::SoundCodeQueue() {}

SoundCodeQueue::~SoundCodeQueue() {}

int SoundCodeQueue::front() {
    std::unique_lock<std::mutex> _lock(_mtx);
    while (internalQueue.empty()){
        _cv.wait(_lock);
    }
    return internalQueue.front();
}

void SoundCodeQueue::push(int element) {
    std::unique_lock<std::mutex> _lock(_mtx);
    internalQueue.push_back(element);
    _cv.notify_one();
}

void SoundCodeQueue::pop() {
    std::unique_lock<std::mutex> _lock(_mtx);
    internalQueue.pop_front();
    _cv.notify_one();
}

bool SoundCodeQueue::empty() {
    std::unique_lock<std::mutex> _lock(_mtx);
    return internalQueue.empty();
}
