//
// Created by camix on 10/06/19.
//

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_messagebox.h>
#include "SwsContext.h"


/// first you need to Initialize libavformat and register all the muxers, demuxers and
/// protocols with av_register_all();
SwsContext::SwsContext(BlockingQueue& producedFrames, Window& window) :
        // Este buffer tiene el tamaño de la sección de SDL que quiero leer, multiplico
        // x3 por la cantidad de bytes (8R,8G,8B)
        // A sws parece que no le gusta este tamaño
        producedFrames(producedFrames),
        width(window.getWindowWidth()),
        height(window.getWindowHeight()),
        dataBuffer(width * height * 3),
        window(window) {
}

SwsContext::~SwsContext() = default;

void SwsContext::write() {
    // Obtengo los bytes de la textura en el buffer
    int res = SDL_RenderReadPixels(window.getRenderer(), NULL, SDL_PIXELFORMAT_RGB24, dataBuffer.data(), width * 3);
    if (res) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "RendererReadPixels error", SDL_GetError(), NULL);
        throw SwsContextRendererReadPixelsException();
    }
    //operacion lenta que pasó a otro thread:
    //videoOutput.writeFrame(dataBuffer.data(), ctx);
    producedFrames.push(dataBuffer);
}
