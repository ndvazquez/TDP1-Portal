//
// Created by camix on 20/05/19.
//

#include <SDL_types.h>
#include "MouseButtonUp.h"

MouseButtonUp::MouseButtonUp(SDL_Event* event) : event(event) {}

Sint32 MouseButtonUp::getX() {
    return event->button.x;
}

Sint32 MouseButtonUp::getY() {
    return event->button.y;
}
