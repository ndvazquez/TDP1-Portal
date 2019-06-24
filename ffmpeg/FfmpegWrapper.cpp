//
// Created by camix on 24/06/19.
//


#include <iostream>
#include "FfmpegWrapper.h"
#include "../ffmpeg/SwsContext.h"

FfmpegWrapper::FfmpegWrapper(Window &window,
                            bool *recordVideo,
                            std::string videoPath) {
    this->recordVideo = recordVideo;
    if (!*recordVideo) {
        ctx = NULL;
        consumer = NULL;
        return;
    }
    av_register_all();  // REALLY IMPORTANT.
                        // If you do not call this function before initializing Cosumer
                        // your program will crash
    ctx = new SwsContext(queue, window);
    consumer = new Consumer(queue, videoPath, window);

    consumer->start();

}

void FfmpegWrapper::run() {
    if (recordVideo && ctx) {
        ctx->write();
    }
}

void FfmpegWrapper::stop() {
    queue.close();      // hey queue when you get empty it means that we finish.
                        // We are not going tu push anything else.
    consumer->join();
}

FfmpegWrapper::~FfmpegWrapper() {
    if (ctx) {
        delete ctx;
    }
    if (consumer) {
        delete consumer;
    }
}
