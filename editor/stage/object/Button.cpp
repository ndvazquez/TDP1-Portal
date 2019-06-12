//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Button.h"

Button::Button(std::string& path, Window& window, const std::string& name, int w, int h) :
    StaticObject(path, window, name, w, h) {}

void Button::setName(std::pair<int, int> position, std::string& enteredName) {
    std::cerr << "Soy un boton ";
    names[position] = enteredName;
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

Button::~Button() = default;
