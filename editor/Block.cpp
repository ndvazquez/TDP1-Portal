//
// Created by camix on 22/05/19.
//

#include <iostream>
#include "Block.h"

Block::Block(std::string &path, Window &window, const std::string& name, int w, int h) :
    StaticObject(path, window, name, w, h) {}

Block::~Block() = default;
