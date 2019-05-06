//
// Created by ndv on 5/5/19.
//

#ifndef PORTAL_SPRITE_H
#define PORTAL_SPRITE_H

#include <SDL.h>
#include <SDL_image.h>
#include <exception>
#include "Window.h"

class SpriteInitException: public std::exception {
    virtual const char* what() const throw () {
        std::string message = "There was an error while trying to initialize a sprite: ";
        message += SDL_GetError();
        return message.c_str();
    }
};

class Sprite {
    SDL_Texture* texture;
    int imageWidth;
    int imageHeight;
public:
    Sprite(const std::string& path, Window& window);
    ~Sprite();
    void free();
    void draw(Window& destWindow, int x, int y, SDL_Rect* destRect);
    int getWidth();
    int getHeight();
};

#endif //PORTAL_SPRITE_H
