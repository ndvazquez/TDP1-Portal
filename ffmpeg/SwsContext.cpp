//
// Created by camix on 10/06/19.
//

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_messagebox.h>
#include "SwsContext.h"


/// first you need to Initialize libavformat and register all the muxers, demuxers and
/// protocols with av_register_all();
SwsContext::SwsContext(std::string filename, Window& window) :
        videoOutput(context, filename),
        width(window.getWindowWidth()),
        height(window.getWindowHeight()),
        ctx(sws_getContext(width, height,
                           AV_PIX_FMT_RGB24,
                           width, height,
                           AV_PIX_FMT_YUV420P,
                           0, 0, 0, 0)) ,
        // Este buffer tiene el tamaño de la sección de SDL que quiero leer, multiplico
        // x3 por la cantidad de bytes (8R,8G,8B)
        // A sws parece que no le gusta este tamaño
        dataBuffer(width * height * 3),
        window(window) {
}

SwsContext::~SwsContext() {
    videoOutput.close();
    // Libero escalador
    sws_freeContext(ctx);
}

void SwsContext::write() {
    // Obtengo los bytes de la textura en el buffer
    int res = SDL_RenderReadPixels(window.getRenderer(), NULL, SDL_PIXELFORMAT_RGB24, dataBuffer.data(), width * 3);
    if (res) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "RendererReadPixels error", SDL_GetError(), NULL);
        throw SwsContextRendererReadPixelsException();
    }
    //operacion lenta que va a tenre que estar en otro thread
    videoOutput.writeFrame(dataBuffer.data(), ctx);
}
