//
// Created by camix on 12/06/19.
//

#include "Thread.h"


Thread::Thread(Thread&& other) {
    this->thread = std::move(other.thread);
}
Thread::Thread() = default;
Thread::~Thread() = default;

void Thread::start() {
    this->thread = std::thread(&Thread::run, this);
}


void Thread::join() {
    this->thread.join();
}
