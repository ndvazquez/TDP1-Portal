//
// Created by cecix on 17/05/19.
//

#include "Button.h"

Button::Button(b2Body* body):
        body(body) {
}

float Button::getHorizontalPosition() {
    return this->body->GetPosition().x;
}

float Button::getVerticalPosition() {
    return this->body->GetPosition().y;
}

