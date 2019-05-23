//
// Created by camix on 22/05/19.
//

#include "MouseButton.h"

MouseButton::MouseButton(SDL_Event* event) : event(event) {}

Sint32 MouseButton::getX() {
    return event->button.x;
}

Sint32 MouseButton::getY() {
    return event->button.y;
}