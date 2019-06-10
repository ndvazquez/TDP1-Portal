//
// Created by camix on 10/06/19.
//

#ifndef PORTAL_FORMATOUTPUT_H
#define PORTAL_FORMATOUTPUT_H


#define INIT_FORMAT_OUTPUT_EXC "No output format was found"

#include <string>

extern "C" {
#include <libavformat/avformat.h>
}

class FormatOutputException : public std::exception {
protected:
    std::string message;
public:
    FormatOutputException() = default;
    virtual const char *what() const throw() {
        return this->message.c_str();
    }
};

class FormatOutputInitException : public FormatOutputException {
public:
    FormatOutputInitException() {
        message = INIT_FORMAT_OUTPUT_EXC;
    }
    explicit FormatOutputInitException(std::string msg) {
        message = msg;
    }
};

class FormatOutput {
private:
    AVOutputFormat* avOutputFormat;
    AVCodec *codec;

public:
    explicit FormatOutput(const std::string& filename);
    ~FormatOutput();
    AVCodec *getCodec();
};



#endif //PORTAL_FORMATOUTPUT_H
