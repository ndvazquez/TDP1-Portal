//
// Created by camix on 22/05/19.
//

#include "Button.h"

Button::Button(std::string &path, Window &window) : StaticObject(path, window) {}

bool Button::canBeOn() {
    return false;
}

Button::~Button() = default;
