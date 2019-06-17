//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Button.h"

Button::Button(std::string &path, Window &window, int id, int w, int h) :
    StaticObject(path, window, id, w, h) {}

void Button::setName(std::pair<int, int>& position, std::string& enteredName) {
    for(auto it = names.begin(); it != names.end(); it++) {
        if (it->second == enteredName && it->first != position) {
            throw SetNameException();
        }
    }
    names[position] = enteredName;
    std::cerr << "Soy un boton ";
    std::cerr << "y mi nombre es " << enteredName << std::endl;
}

bool Button::doesThisNameExist(std::string &string) {
    auto it = this->names.begin();
    for(; it != this->names.end(); it++) {
       if (it->second == string) {
           return true;
       }
    }
    return false;
}

void Button::removeFrom(int x, int y, std::map<std::pair<int, int>, int> &tiles,
                        std::unordered_map<int, Object *> &textures) {
    names.erase(std::make_pair(x, y));
    Object::removeFrom(x, y, tiles, textures);
}

Button::~Button() = default;

std::pair<float, float> Button::centerOfMass(const std::pair<int, int> &position) {
    return this->rectangleCenterOfMass(position, BUTTON_WIDTH, BUTTON_HEIGHT);
}
