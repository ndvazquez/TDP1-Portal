//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Block.h"

Block::Block(const std::string &path, Window &window, const std::string& name) :
    StaticObject(path, window, name) {}

bool Block::canBeOn(const std::string &name) {
    return !(name == "Chell");
}

bool Block::canBeOn() {
    return true;
}

Block::~Block() = default;
