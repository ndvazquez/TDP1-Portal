//
// Created by camix on 22/05/19.
//

#include <string>
#include "Rock.h"
#include "../common/Window.h"

Rock::Rock(std::string &path, Window &window) : StaticObject(path, window) {}

bool Rock::canBeOn() {
    return false;
}

Rock::~Rock() = default;
