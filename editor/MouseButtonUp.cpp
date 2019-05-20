//
// Created by camix on 20/05/19.
//

#include <SDL_types.h>
#include "MouseButtonUp.h"

MouseButtonUp::MouseButtonUp(Sint32 x, Sint32 y) : x(x), y(y) {}

Sint32 MouseButtonUp::getX() {
    return x;
}

Sint32 MouseButtonUp::getY() {
    return y;
}
