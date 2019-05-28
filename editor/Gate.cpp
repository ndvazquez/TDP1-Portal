//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Gate.h"

Gate::Gate(std::string& path, Window& window, const std::string& name, int w, int h) :
    StaticObject(path, window, name, w, h) {}

void Gate::draw(SDL_Rect* rect) {
    SDL_Rect newRect = {rect->x, rect->y - rect->h, rect->w, rect->h*2};
    StaticObject::draw(&newRect);
}

Gate::~Gate() = default;


void Gate::setName() {
    std::cerr << "Soy una compuerta" << std::endl;
}
