//
// Created by camix on 12/06/19.
//

#ifndef PORTAL_THREAD_H
#define PORTAL_THREAD_H



#include <thread>

class Thread {
private:
    std::thread thread;

public:
    Thread();
    void start();
    void join();
    virtual void run() = 0;
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    virtual ~Thread();
    Thread(Thread&& other);
};

#endif //PORTAL_THREAD_H
