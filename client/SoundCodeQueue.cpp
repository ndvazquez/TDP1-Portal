//
// Created by ndv on 6/2/19.
//

#include "SoundCodeQueue.h"

SoundCodeQueue::SoundCodeQueue() {}

SoundCodeQueue::~SoundCodeQueue() {}

int SoundCodeQueue::front() {
    if (internalQueue.empty()){
        return -1;
    }
    return internalQueue.front();
}

void SoundCodeQueue::push(int element) {
    internalQueue.push_back(element);
}

void SoundCodeQueue::pop() {
    internalQueue.pop_front();
}

bool SoundCodeQueue::empty() {
    return internalQueue.empty();
}
