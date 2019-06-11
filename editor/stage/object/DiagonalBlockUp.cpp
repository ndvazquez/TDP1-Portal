//
// Created by camix on 11/06/19.
//

#include "DiagonalBlockUp.h"

DiagonalBlockUp::DiagonalBlockUp(std::string &path, Window &window, const std::string& name, int w, int h) :
        StaticObject(path, window, name, w, h) {}

bool DiagonalBlockUp::hasGravity() {
    return false;
}

DiagonalBlockUp::~DiagonalBlockUp() = default;