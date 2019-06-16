//
// Created by camix on 10/06/19.
//

#include "Acid.h"

Acid::Acid(std::string& path, Window& window, int totalFrames ,const std::string& name, int w, int h) :
        AnimatedObject(path, window, totalFrames, name, w, h) {}

Acid::~Acid() = default;

void Acid::draw(SDL_Rect* rect) {
    SDL_Rect newRect = {rect->x, rect->y + rect->h/2, rect->w, rect->h/2};
    AnimatedObject::draw(&newRect);
}

std::pair<float, float> Acid::centerOfMass(const std::pair<int, int> &position) {
    return this->rectangleCenterOfMass(position, ACID_WIDTH, ACID_HEIGHT);
}