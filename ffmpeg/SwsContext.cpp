//
// Created by camix on 10/06/19.
//

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_messagebox.h>
#include "SwsContext.h"

const int BUFFER_WIDTH = 352, BUFFER_HEIGHT = 288;

/// first you need to Initialize libavformat and register all the muxers, demuxers and
/// protocols with av_register_all();
SwsContext::SwsContext(std::string filename) :
        videoOutput(context, filename),
        ctx(sws_getContext(BUFFER_WIDTH, BUFFER_HEIGHT,
                           AV_PIX_FMT_RGB24, BUFFER_WIDTH, BUFFER_HEIGHT,
                           AV_PIX_FMT_YUV420P, 0, 0, 0, 0)) ,
        // Este buffer tiene el tamaño de la sección de SDL que quiero leer, multiplico
        // x3 por la cantidad de bytes (8R,8G,8B)
        // A sws parece que no le gusta este tamaño
        dataBuffer(BUFFER_WIDTH*BUFFER_HEIGHT*3) {}

SwsContext::~SwsContext() {
    videoOutput.close();
    // Libero escalador
    sws_freeContext(ctx);
}

void SwsContext::write(SdlWindow& window) {
    // Obtengo los bytes de la textura en el buffer
    int res = SDL_RenderReadPixels(window.getRenderer(), NULL, SDL_PIXELFORMAT_RGB24, dataBuffer.data(), BUFFER_WIDTH * 3);
    if (res) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "RendererReadPixels error", SDL_GetError(), NULL);
        throw SwsContextRendererReadPixelsException();
    }
    //operacion lenta que va a tenre que estar en otro thread
    videoOutput.writeFrame(dataBuffer.data(), ctx);
}
