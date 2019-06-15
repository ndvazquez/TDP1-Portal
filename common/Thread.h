//
// Created by ndv on 6/15/19.
//

#ifndef PORTAL_THREAD_H
#define PORTAL_THREAD_H

#include <thread>

class Thread {
public:
    Thread();
    void start();
    void join();
    bool isDead();
    virtual void run() = 0;
    virtual void stop() = 0;
    virtual ~Thread();
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    Thread(Thread&& other);
    Thread& operator=(Thread&& other);
private:
    std::thread thread;
protected:
    bool _isDead;

};


#endif //PORTAL_THREAD_H
