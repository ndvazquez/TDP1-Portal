//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Chell.h"

Chell::Chell(std::string& path, Window& window, int totalFrames ,const std::string& name, int w, int h) :
        AnimatedObject(path, window, totalFrames, name, w, h) {}

Chell::~Chell() = default;

void Chell::draw(SDL_Rect* rect) {
    SDL_Rect newRect = {rect->x, rect->y - rect->h, rect->w, rect->h * h};
    AnimatedObject::draw(&newRect);
}
