//
// Created by camix on 10/06/19.
//

#include "FormatContext.h"
#include <stdexcept>
#include <string>
extern "C" {
#include <libavformat/avformat.h>
}

FormatContext::FormatContext() {
    this->pFormatCtx = avformat_alloc_context();
}

FormatContext::~FormatContext() {
    avformat_free_context(this->pFormatCtx);
}

AVFormatContext * FormatContext::getContext() const {
    return this->pFormatCtx;
}
