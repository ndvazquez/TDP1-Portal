//
// Created by camix on 17/06/19.
//

#include "DiagonalBlockDown.h"


DiagonalBlockDown::DiagonalBlockDown(std::string &path, Window &window,
                                     int id, int w, int h) :
        StaticObject(path, window, id, w, h) {}

bool DiagonalBlockDown::hasGravity() {
    return false;
}

DiagonalBlockDown::~DiagonalBlockDown() = default;