//
// Created by ndv on 5/11/19.
//

#ifndef PORTAL_SDLSESSION_H
#define PORTAL_SDLSESSION_H

#include <SDL.h>
#include <SDL_image.h>
#include <exception>
#include <string>

class SDLInitException: public std::exception {
    virtual const char* what() const throw () {
        std::string message = "There was an error initializing SDL: ";
        message += SDL_GetError();
        return message.c_str();
    }
};

class IMGInitException: public std::exception {
    virtual const char* what() const throw () {
        std::string message = "Failed to init required image support: ";
        message += IMG_GetError();
        return message.c_str();
    }
};

// Wrapper to make SDL initialization RAII compliant.
class SDLSession {
public:
    SDLSession(uint32_t initFlags);
    ~SDLSession();
};

#endif //PORTAL_SDLSESSION_H
