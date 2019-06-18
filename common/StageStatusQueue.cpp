//
// Created by ndv on 6/15/19.
//

#include "StageStatusQueue.h"
#include <string>

StageStatusQueue::StageStatusQueue() {
}

StageStatusQueue::~StageStatusQueue() {}

void StageStatusQueue::push(const std::string& stageStatus) {
    std::unique_lock<std::mutex> _lock(_mtx);
    internalQueue.push(stageStatus);
    _cv.notify_one();
}

std::string StageStatusQueue::pop() {
    std::unique_lock<std::mutex> _lock(_mtx);
    while (internalQueue.empty()){
        _cv.wait(_lock);
    }
    std::string stageStatus = internalQueue.front();
    internalQueue.pop();
    return stageStatus;
}

bool StageStatusQueue::empty() {
    std::unique_lock<std::mutex> _lock(_mtx);
    return internalQueue.empty();
}