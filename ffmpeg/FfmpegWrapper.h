//
// Created by camix on 24/06/19.
//

#ifndef PORTAL_FFMPEGWRAPPER_H
#define PORTAL_FFMPEGWRAPPER_H


#include "BlockingQueue.h"
#include "../common/Window.h"

#include "../ffmpeg/Consumer.h"

class FfmpegWrapper {
private:
    BlockingQueue queue;
    Consumer* consumer;
    SwsContext* ctx;
    bool *recordVideo;

public:
    FfmpegWrapper(Window& window, bool *recordVideo, std::string videoPath);
    ~FfmpegWrapper();

    void run();
    void stop();
};


#endif //PORTAL_FFMPEGWRAPPER_H
