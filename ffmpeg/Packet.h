//
// Created by camix on 10/06/19.
//

#ifndef PORTAL_PACKET_H
#define PORTAL_PACKET_H


#define INIT_PKT_EXC "There was an error while allocating memory for a Packet\n"

#include <string>

extern "C" {
#include <libavcodec/avcodec.h>
}

class PacketException : public std::exception {
protected:
    std::string message;
public:
    PacketException() = default;
    virtual const char *what() const throw() {
        return this->message.c_str();
    }
};

class PacketInitException : public PacketException {
public:
    PacketInitException() {
        message = INIT_PKT_EXC;
    }
};

class Packet {
private:
    AVPacket* pkt;

public:
    Packet();
    ~Packet();

    AVPacket *get();

    void write(FILE *outfile);
};


#endif //PORTAL_PACKET_H
