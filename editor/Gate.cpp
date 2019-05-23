//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Gate.h"

Gate::Gate(const std::string &path, Window &window, const std::string& name) :
    StaticObject(path, window, name) {}

bool Gate::canBeOn() {
    return false;
}

void Gate::draw(SDL_Rect* rect) {
    SDL_Rect newRect = {rect->x, rect->y - rect->h, rect->w, rect->h*2};
    StaticObject::draw(&newRect);
}

Gate::~Gate() = default;

void Gate::addTo(int x, int y, std::map<std::pair<int, int>, std::string>& tiles) {
    Object::addWithGravityTo(x, y, tiles);
}

void Gate::setName() {
    std::cerr << "Soy una compuerta" << std::endl;
}
