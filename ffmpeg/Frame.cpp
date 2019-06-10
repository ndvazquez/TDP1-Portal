//
// Created by camix on 10/06/19.
//

#include "Frame.h"
extern "C" {
#include <libswscale/swscale.h>
}

Frame::Frame(int format, int width, int height) : frame(av_frame_alloc()){
    if (!frame){
        throw FrameInitException();
    }

    this->frame->format = format;
    this->frame->width  = width;
    this->frame->height = height;

    av_frame_get_buffer(this->frame, 0);
    this->currentPts = 0;
}


Frame::~Frame() {
    av_frame_free(&frame);
}

void Frame::write(const char *data, SwsContext *ctx) {
    const u_int8_t* tmp = (const u_int8_t*) data;
    // El ancho del video x3 por la cantidad de bytes
    int width = 352 * 3;
    sws_scale(ctx, &tmp, &width, 0, frame->height, frame->data, frame->linesize);
    frame->pts = currentPts;
    currentPts++;
}
