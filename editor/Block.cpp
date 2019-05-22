//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Block.h"

Block::Block(std::string &path, Window &window) :
    StaticObject(path, window) {}

bool Block::canBeOn(const std::string &name) {
    std::cerr << "Preguntandole a block: " << std::endl;
    return true;
}

bool Block::canBeOn() {
    return true;
}

Block::~Block() = default;
