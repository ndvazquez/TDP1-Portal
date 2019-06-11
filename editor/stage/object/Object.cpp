//
// Created by camix on 22/05/19.
//

#include <utility>
#include <iostream>
#include "Object.h"
#define SENTINEL ""

Object::Object(std::string name, int w, int h) :
        name(std::move(name)), w(w), h(h) {}

void Object::hasToBeOn(const std::string &name) {
    floors.push_back(name);
}

void Object::addWithGravityTo(int x, int y, std::map<std::pair<int, int>, std::string>& tiles) {
    for (int i = 0; i < w; i++) {
        // if we dont have something under us there is no way to be add.
        auto positionBelow = tiles.find(std::make_pair(x + i, y + 1));
        if (positionBelow == tiles.end()) {
            throw AddTileGravityException(this->name);
        }

        // now, we have something but it can not be just anything
        std::string &under = positionBelow->second;
        auto possibleFloor = floors.begin();
        for (; possibleFloor != floors.end(); possibleFloor++) {
            if (*possibleFloor == under) {
                break;
            }
        }
        if (possibleFloor == floors.end()) {
            throw AddTileGravityException(this->name);
        }
    }
    // is something we can be on!!!
    //Object::addTo(x,y,tiles);
}

void Object::addTo(int x, int y, std::map<std::pair<int, int>,
        std::string> &tiles) {
    if(this->hasGravity()) {
        this->addWithGravityTo(x, y, tiles);
    }

    // If there's nothing in the space i need
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            auto it = tiles.find(std::make_pair(x - i, y- j));
            if (it != tiles.end()) { //} || x - i < 0 || y - j < 0) { ;
                throw AddTileTakenPositionException(this->name);
            }
        }
    }

    tiles.insert(std::make_pair(std::make_pair(x, y), this->name));
    // I add my self in all that space
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            tiles.insert(std::make_pair(std::make_pair(x - i, y - j), SENTINEL));
        }
    }

}


void Object::removeFrom(int x, int y, std::map<std::pair<int, int>, std::string> &tiles,
                        std::unordered_map<std::string, Object *>& textures) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            tiles.erase(std::make_pair(x - i , y - j));
        }
    }
}

void Object::setName() {
    // if is not overwritten it wont do much
    // i.e. if you are not a button or a gate u must do nothing
}

bool Object::hasGravity() {
    return true;
}
