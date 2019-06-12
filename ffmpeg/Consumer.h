//
// Created by camix on 12/06/19.
//

#ifndef PORTAL_CONSUMER_H
#define PORTAL_CONSUMER_H


#include "Thread.h"
#include "BlockingQueue.h"
#include "Output.h"
#include "FormatContext.h"
#include "../common/Window.h"

class Consumer : public Thread  {
private:
    BlockingQueue& producedFrames;
    FormatContext context;
    Output videoOutput;
    // You need it to perform scaling/conversion operations using.
    SwsContext* ctx;

public:
    /// first you need to Initialize libavformat and register all the muxers, demuxers and
    /// protocols with av_register_all();
    Consumer(BlockingQueue& producedImages, std::string& filename, Window& window);

    ~Consumer();

    virtual void run() override;

};


#endif //PORTAL_CONSUMER_H
