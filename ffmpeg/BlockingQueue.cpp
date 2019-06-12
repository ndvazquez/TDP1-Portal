//
// Created by camix on 12/06/19.
//

#include "BlockingQueue.h"
#include <vector>

BlockingQueue::BlockingQueue() {
    this->done = false;
}

BlockingQueue::~BlockingQueue() = default;

void BlockingQueue::push(std::vector<char> element) {
    std::unique_lock<std::mutex> lock(this->m);
    this->queue.push(element);
    this->cond_variable.notify_all();
}

void BlockingQueue::close() {
    std::vector<char> s;
    push(s);
}

std::vector<char> BlockingQueue::pop() {
    std::unique_lock<std::mutex> lock(this->m);

    if (this->done)
        throw BlockingQueueDoneException();
    int i = 0;
    while (this->queue.empty() && ! this->done) {
        this->cond_variable.wait(lock);
        i++;
    }

    if (this->done)
        throw BlockingQueueDoneException();

    std::vector<char> data = this->queue.front();
    this->queue.pop();
    if (data.empty()) {
        this->done = true;
        throw BlockingQueueDoneException();
    }
    return data;
}