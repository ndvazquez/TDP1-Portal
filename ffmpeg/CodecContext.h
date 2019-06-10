//
// Created by camix on 10/06/19.
//

#ifndef PORTAL_CODECCONTEXT_H
#define PORTAL_CODECCONTEXT_H


extern "C" {
#include <libavcodec/avcodec.h>
}
#include <string>
#define INIT_CODEC_CONTEXT_EXC "There was an error while allocating memory for a CodecContext\n"

class CodecContextException : public std::exception {
protected:
    std::string message;
public:
    explicit CodecContextException() = default;
    virtual const char *what() const throw() {
        return this->message.c_str();
    }
};

class CodecContextInitException : public CodecContextException {
public:
    explicit CodecContextInitException() {
        message = INIT_CODEC_CONTEXT_EXC;
    }
};

class CodecContext {
private:
    AVCodecContext* codecContext;

public:
    explicit CodecContext(AVCodec *codec);

    ~CodecContext();

    AVCodecContext *get();

    int getHeight();

    int getWidth();

    int getPixFmt();
};

#endif //PORTAL_CODECCONTEXT_H
