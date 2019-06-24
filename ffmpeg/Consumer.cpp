//
// Created by camix on 12/06/19.
//

#include "Consumer.h"
extern "C" {
#include <libswscale/swscale.h>
}

Consumer::Consumer(BlockingQueue& producedFrames, std::string& filename, Window& window) :
        producedFrames(producedFrames),
        videoOutput(context, filename, window),
        ctx(sws_getContext(window.getWindowWidth(), window.getWindowHeight(),
                           AV_PIX_FMT_RGB24, window.getWindowWidth(), window.getWindowHeight(),
                           AV_PIX_FMT_YUV420P, 0, 0, 0, 0))  {
}

void Consumer::run() {
    try {
        while (true) {
            std::vector<char> frame = this->producedFrames.pop();
            videoOutput.writeFrame(frame.data(), ctx);
        }
    }
    catch (BlockingQueueDoneException& e) {
        return;
    }
}

Consumer::~Consumer() {
    videoOutput.close();
    sws_freeContext(ctx);
}