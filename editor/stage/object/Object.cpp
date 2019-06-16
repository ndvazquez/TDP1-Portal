//
// Created by camix on 22/05/19.
//

#include <utility>
#include <iostream>
#include "Object.h"


Object::Object(std::string name, int w, int h) :
        name(std::move(name)), w(w), h(h) {}

void Object::hasToBeOn(const std::string &name) {
    floors.push_back(name);
}

void Object::addWithGravityTo(int x, int y, std::map<std::pair<int, int>,std::string>
                        &tiles,
                        std::unordered_map<std::string, Object *>& textures) {
    for (int i = 0; i < w; i++) {
        // if we dont have something under us there is no way to be add.
        auto positionBelow = tiles.find(std::make_pair(x + i, y + 1));
        if (positionBelow == tiles.end()) {
            std::cerr << "No tengo nada abajo" << std::endl;
            throw AddTileGravityException(this->name);
        }
        std::cerr << "Si tengo nada abajo" << std::endl;

        // now, we have something
        std::string &under = positionBelow->second;
        // but it can not be just anything
        if(textures[under]->hasGravity()) {
            throw AddTileGravityException(this->name);
        }
    }
}

void Object::addTo(int x, int y, std::map<std::pair<int, int>,std::string>
        &tiles,
        std::unordered_map<std::string, Object *>& textures,
        bool needGravitySentinel) {
    std::string sentinel = WITHOUT_GRAVITY_SENTINEL;

    if (needGravitySentinel) {
        sentinel = GRAVITY_SENTINEL;
    }
    if(this->hasGravity()) {
        sentinel = GRAVITY_SENTINEL;
        std::cerr << "Soy "<< name <<" y tengo gravedad" << std::endl;
        this->addWithGravityTo(x, y, tiles, textures);
    }

    // If there's nothing in the space i need
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            auto it = tiles.find(std::make_pair(x + i, y- j));
            if (it != tiles.end()) { //} || x - i < 0 || y - j < 0) { ;
                throw AddTileTakenPositionException(this->name);
            }
        }
    }

    tiles.insert(std::make_pair(std::make_pair(x, y), this->name));
    // I add my self in all that space
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            tiles.insert(std::make_pair(std::make_pair(x + i, y - j), sentinel));
        }
    }
    std::pair<int, int> pair = std::make_pair(x, y);
}


void Object::removeFrom(int x, int y, std::map<std::pair<int, int>, std::string> &tiles,
                        std::unordered_map<std::string, Object *>& textures) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            tiles.erase(std::make_pair(x + i , y - j));
        }
    }
}

void Object::setName(std::pair<int, int>& position, std::string& enteredName) {
    // if is not overwritten it wont do much
    // i.e. if you are not a button or a gate u must do nothing
}

void Object::addCondition(std::pair<int, int> position, std::string &condition) {
    // if is not overwritten it wont do much
    // i.e. if you are not a gate u must do nothing
}

bool Object::hasGravity() {
    return true;
}

bool Object::doesThisNameExist(std::string &string) {
    return false;
}

bool Object::hasCondition() {
    return false;
}




std::string Object::getMetersPosition(const std::pair<int, int> position) {
    std::string s;
    s = "(" + std::to_string(position.first) + "," + std::to_string(position.second) + ")";
    return s;
}



