//
// Created by camix on 20/05/19.
//

#include "MouseButtonDown.h"

MouseButtonDown::MouseButtonDown(Sint32 x, Sint32 y) : x(x), y(y) {}

Sint32 MouseButtonDown::getX() {
    return x;
}

Sint32 MouseButtonDown::getY() {
    return y;
}