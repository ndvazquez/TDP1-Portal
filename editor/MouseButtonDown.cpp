//
// Created by camix on 20/05/19.
//

#include "MouseButtonDown.h"

MouseButtonDown::MouseButtonDown(SDL_Event* event) : event(event) {}

Sint32 MouseButtonDown::getX() {
    return event->button.x;
}

Sint32 MouseButtonDown::getY() {
    return event->button.y;
}