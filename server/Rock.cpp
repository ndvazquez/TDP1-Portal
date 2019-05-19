//
// Created by cecix on 17/05/19.
//

#include "Rock.h"

Rock::Rock(b2Body* body):
        body(body) {
}

float Rock::getHorizontalPosition() {
    return this->body->GetPosition().x;
}

float Rock::getVerticalPosition() {
    return this->body->GetPosition().y;
}
