//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Button.h"

Button::Button(std::string &path, Window &window) : StaticObject(path, window) {}

bool Button::canBeOn() {
    return false;
}

bool Button::canBeAdd(int x, int y, std::map<std::pair<int, int>, std::string> &names) {
    auto it = names.find(std::make_pair(x, y + 1));
    if (it == names.end()) {
        return false;
    }
    return Object::canBeOn(it->second);
}

void Button::setName() {
    std::cerr << "Soy un boton" << std::endl;
}

Button::~Button() = default;
