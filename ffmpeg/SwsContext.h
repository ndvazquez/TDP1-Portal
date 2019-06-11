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
extern "C" {
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}
#define RRP_SWS_CONTEXT_EXC "There was an error while writing the frame\n"

class SwsContextException : public std::exception {
protected:
    std::string message;
public:
    SwsContextException() = default;
    virtual const char *what() const throw() {
        return this->message.c_str();
    }
};

class SwsContextRendererReadPixelsException : public SwsContextException {
public:
    SwsContextRendererReadPixelsException() {
        message = RRP_SWS_CONTEXT_EXC;
    }
};

// RAII wrapper for struct SwsContext
class SwsContext {
private:
    FormatContext context;
    Output videoOutput;
    int width;
    int height;
    // You need it to perform scaling/conversion operations using.
    SwsContext* ctx;
    std::vector<char> dataBuffer;
    Window& window;


public:
    explicit SwsContext(std::string filename, Window& window);
    ~SwsContext();
    void write();
};



#endif //PORTAL_SWSCONTEXT_H
