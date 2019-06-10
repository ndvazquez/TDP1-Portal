//
// Created by camix on 10/06/19.
//

extern "C" {
#include <libavutil/opt.h>
}

#include "FormatOutput.h"
#include "CodecContext.h"

FormatOutput::FormatOutput(const std::string& filename) {
    // Intenta deducir formato según extensión
    this->avOutputFormat = av_guess_format(NULL, filename.c_str(), NULL);
    if (!this->avOutputFormat) {
        // Intenta usar el formato standard
        this->avOutputFormat = av_guess_format("mpeg", NULL, NULL);
    }
    if (!this->avOutputFormat) {
        throw FormatOutputInitException();
    }
    // h.264 es bastante popular, pero hay mejores
    this->avOutputFormat->video_codec = AV_CODEC_ID_H264;



    this->codec = avcodec_find_encoder(this->avOutputFormat->video_codec);
    if (!codec) {
        throw FormatOutputInitException("No se pudo instanciar codec");
    }
    //codecContext.init(codec);
}


AVCodec *FormatOutput::getCodec() {
    return this->codec;
}


FormatOutput::~FormatOutput() {

}
