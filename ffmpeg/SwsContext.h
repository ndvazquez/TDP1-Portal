//
// Created by camix on 10/06/19.
//

#ifndef PORTAL_SWSCONTEXT_H
#define PORTAL_SWSCONTEXT_H


#include <string>
#include <vector>
#include "FormatContext.h"
#include "Output.h"
#include "../common/Window.h"
#include "BlockingQueue.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}
#define RRP_SWS_CONTEXT_EXC "There was an error while writing the frame\n"



// RAII wrapper for struct SwsContext
class SwsContext {
private:
    BlockingQueue& producedFrames;
    int width;
    int height;
    std::vector<char> dataBuffer;
    Window& window;


public:
    explicit SwsContext(BlockingQueue& producedFrames, Window& window);
    ~SwsContext();
    void write();
};

class SwsContextRendererReadPixelsException : public std::exception {
public:
    SwsContextRendererReadPixelsException() = default;
    virtual const char *what() const throw() {
        return RRP_SWS_CONTEXT_EXC;
    }
};

#endif //PORTAL_SWSCONTEXT_H
