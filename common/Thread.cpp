//
// Created by ndv on 6/15/19.
//

#include "Thread.h"

Thread::Thread() : _isDead(false) {}

Thread::~Thread() {
}

void Thread::start() {
    thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    thread.join();
}

Thread::Thread(Thread&& other) {
    this->thread = std::move(other.thread);
}

Thread& Thread::operator=(Thread&& other) {
    this->thread = std::move(other.thread);
    return *this;
}

bool Thread::isDead(){
    return _isDead;
}

