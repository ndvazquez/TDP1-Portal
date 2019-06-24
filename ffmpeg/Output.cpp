//
// Created by camix on 10/06/19.
//

#include "Output.h"
#include "FormatContext.h"
#include <cstdio>
#include <string>
#include <stdexcept>
#include <iostream>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
}

static void encode(CodecContext* codecContext, Frame* frame, Packet* pkt,
                   FILE *outfile) {
    int ret = 0;
    AVCodecContext* enc_ctx = codecContext->get();
    if (!frame) {
        ret = avcodec_send_frame(enc_ctx, NULL);
    } else {
        ret = avcodec_send_frame(enc_ctx, frame->get());
    }
    if (ret < 0) {
        throw std::runtime_error("Error al enviar frame");
    }
    while (ret >= 0) {
        ret = avcodec_receive_packet(enc_ctx, pkt->get());
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0) {
            throw std::runtime_error("Error al codificar");
        }
        pkt->write(outfile);
    }
}

Output::Output(FormatContext &context, const std::string &filename, Window &window) :
        context(context) ,
        format(filename),
        codecContext(format.getCodec(), window),
        frame(codecContext.getPixFmt(), codecContext.getWidth(), codecContext.getHeight()) {
    this->outputFile = fopen(filename.c_str(), "wb");
}

void Output::close() {
    encode(&codecContext, nullptr, &pkt, this->outputFile);
    // add sequence end code to have a real MPEG file
    uint8_t endCode[] = { 0, 0, 1, 0xb7 };
    fwrite(endCode, 1, sizeof(endCode), this->outputFile);
}


/// Esto el run/start?
void Output::writeFrame(const char* data, SwsContext* ctx) {
    frame.write(data, ctx);
    encode(&codecContext, &frame, &pkt, outputFile);
}


Output::~Output() {
    fclose(this->outputFile);
}
