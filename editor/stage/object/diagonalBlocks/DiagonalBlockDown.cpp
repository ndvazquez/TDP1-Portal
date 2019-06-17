//
// Created by camix on 17/06/19.
//

#include "DiagonalBlockDown.h"


DiagonalBlockDown::DiagonalBlockDown(std::string &path, Window &window,
                                const std::string& name, int w, int h) :
        StaticObject(path, window, name, w, h) {}

bool DiagonalBlockDown::hasGravity() {
    return false;
}

DiagonalBlockDown::~DiagonalBlockDown() = default;