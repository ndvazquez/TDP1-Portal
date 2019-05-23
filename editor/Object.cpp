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

void Object::addTo(int x, int y, std::map<std::pair<int, int>,
        std::string> &tiles) {
    auto it = tiles.find(std::make_pair(x, y));
    if (it != tiles.end()) {;
        throw StageObjectTakenPositionException(this->name);
    }

    // if (x,y) empty we are ready to go.
    tiles.insert(std::make_pair(std::make_pair(x, y), this->name));
}

void Object::addWithGravityTo(int x, int y, std::map<std::pair<int, int>, std::string>& tiles) {
    // if we dont have something under us there is no way to be add.
    auto it = tiles.find(std::make_pair(x, y + 1));
    if (it == tiles.end()) {
        throw StageObjectAddTileGravityException(this->name);
    }
    Object::addTo(x,y,tiles);
}

Object::Object(const std::string &name) : name(name) {}
