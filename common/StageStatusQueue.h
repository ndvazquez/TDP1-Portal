//
// Created by ndv on 6/15/19.
//

#ifndef PORTAL_STAGESTATUSQUEUE_H
#define PORTAL_STAGESTATUSQUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>

class StageStatusQueue {
    std::condition_variable _cv;
    std::mutex _mtx;
    std::queue<std::string> internalQueue;

public:
    StageStatusQueue();
    ~StageStatusQueue();
    void push(const std::string& stageStatus);
    std::string pop();
    bool empty();
};


#endif //PORTAL_STAGESTATUSQUEUE_H
