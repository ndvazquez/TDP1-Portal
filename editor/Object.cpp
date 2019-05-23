//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Object.h"

void Object::hasToBeOn(const std::string &name) {
    floors.push_back(name);
}

bool Object::canBeOn(const std::string &name) {
    if (name == "Chell") return false;
    auto it = floors.begin();
    for (; it != floors.end(); it++) {
        if (*it == name) {
            return true;
        }
    }
    return false;
}

void Object::setName() {}
