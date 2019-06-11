//
// Created by ndv on 5/5/19.
//

#ifndef PORTAL_SPRITE_H
#define PORTAL_SPRITE_H

#include <SDL.h>
#include <SDL_image.h>
#include <exception>
#include "Window.h"
#include <string>

class SpriteInitException: public std::exception {
    virtual const char* what() const throw() {
        std::string message = "There was an error initializing the sprite: ";
        message += SDL_GetError();
        return message.c_str();
    }
};

class Sprite {
protected:
    Window& window;
    SDL_Texture* texture;
    int imageWidth;
    int imageHeight;
public:
    Sprite(const std::string& path, Window& window);
    virtual ~Sprite();
    void free();
    // Draw the whole texture to a given coordinate.
    void draw(int x, int y);
    // Draw the whole texture to a given rectangle on the window.
    void draw(SDL_Rect* destRect);
    virtual int getWidth();
    virtual int getHeight();
};

#endif //PORTAL_SPRITE_H
