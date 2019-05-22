//
// Created by camix on 22/05/19.
//

#include "Gate.h"

Gate::Gate(std::string &path, Window &window) :
    StaticObject(path, window) {}

bool Gate::canBeOn() {
    return false;
}

Gate::~Gate() = default;
