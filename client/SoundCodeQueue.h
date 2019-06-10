//
// Created by ndv on 6/2/19.
//

#ifndef PORTAL_SOUNDCODEQUEUE_H
#define PORTAL_SOUNDCODEQUEUE_H

#include <deque>

class SoundCodeQueue {
    std::deque<int> internalQueue;
public:
    SoundCodeQueue();
    ~SoundCodeQueue();
    void push(int element);
    int front();
    void pop();
    bool empty();
};


#endif //PORTAL_SOUNDCODEQUEUE_H
