//
// Created by camix on 10/06/19.
//

extern "C" {
#include <libavutil/opt.h>
}
#include "CodecContext.h"

CodecContext::CodecContext(AVCodec *codec) :
        codecContext(avcodec_alloc_context3(codec)) {
    if (!codecContext) {
        throw CodecContextInitException();
    }
    // La resolución debe ser múltiplo de 2
    this->codecContext->width = 352;
    this->codecContext->height = 288;
    this->codecContext->time_base = {1,25};
    this->codecContext->framerate = {25,1};
    this->codecContext->pix_fmt = AV_PIX_FMT_YUV420P;
    this->codecContext->gop_size = 10;
    this->codecContext->max_b_frames = 2;
    if (codec->id == AV_CODEC_ID_H264) {
        this->codecContext->profile = FF_PROFILE_H264_BASELINE;
        av_opt_set(this->codecContext->priv_data, "preset", "slow", 0);
    }
    avcodec_open2(this->codecContext, codec, NULL);
}

CodecContext::~CodecContext() {
    avcodec_close(this->codecContext);
    avcodec_free_context(&this->codecContext);
}


int CodecContext::getPixFmt() {
    return this->codecContext->pix_fmt;
}


int CodecContext::getWidth() {
    return this->codecContext->width;
}

int CodecContext::getHeight() {
    return this->codecContext->height;
}

AVCodecContext* CodecContext::get() {
    return this->codecContext;
}