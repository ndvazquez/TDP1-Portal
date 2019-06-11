//
// Created by camix on 11/06/19.
//

#include "DiagonalBlock.h"

DiagonalBlock::DiagonalBlock(std::string &path, Window &window, const std::string& name, int w, int h) :
        StaticObject(path, window, name, w, h) {}

bool DiagonalBlock::hasGravity() {
    return false;
}

DiagonalBlock::~DiagonalBlock() = default;