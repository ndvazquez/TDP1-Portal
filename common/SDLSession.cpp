//
// Created by ndv on 5/11/19.
//

#include "SDLSession.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

SDLSession::SDLSession(uint32_t initFlags) {
    if (SDL_Init(initFlags) < 0){
        throw SDLInitException();
    }
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)){
        throw IMGInitException();
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        throw MixInitException();
    }
}

SDLSession::~SDLSession() {
    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
}
