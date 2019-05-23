//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Gate.h"

Gate::Gate(std::string &path, Window &window) :
    StaticObject(path, window) {}

bool Gate::canBeOn() {
    return false;
}

void Gate::draw(SDL_Rect* rect) {
    SDL_Rect newRect = {rect->x, rect->y - rect->h, rect->w, rect->h*2};
    StaticObject::draw(&newRect);
}

Gate::~Gate() = default;

bool Gate::canBeAdd(int x, int y, std::map<std::pair<int, int>, std::string> &names) {
    auto below = names.find(std::make_pair(x, y + 1));
    auto over = names.find(std::make_pair(x, y - 1));
    return (below != names.end() && Object::canBeOn(below->second) && y != 0  && over == names.end());
}

void Gate::setName() {
    std::cerr << "Soy una compuerta" << std::endl;
}
