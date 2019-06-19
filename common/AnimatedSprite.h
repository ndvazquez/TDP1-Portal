//
// Created by ndv on 5/6/19.
//

#ifndef PORTAL_ANIMATEDSPRITE_H
#define PORTAL_ANIMATEDSPRITE_H

#include "Window.h"
#include "Sprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include <exception>
#include <string>

class AnimatedSprite : public Sprite {
    // We define a frame width and height, to preserve the original sprite sheet
    // width and height in case we need it for something.
    int frameWidth;
    int frameHeight;
    int frames;
    int currentFrame;
    // Step to render the current frame on the sprite sheet.
    int currentFrameStep;
    unsigned long timeSinceLastUpdate;
    int framerate;
public:
    AnimatedSprite(const std::string& path, Window& window, int totalFrames);
    ~AnimatedSprite();
    void draw(int x, int y, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void draw(SDL_Rect* destRect, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void draw(int x, int y, double angle);
    void draw(SDL_Rect* destRect, double angle);
    void updateFrameStep();
    int getWidth();
    int getHeight();
    void setFrameRate(int newFrameRate);
};


#endif //PORTAL_ANIMATEDSPRITE_H
