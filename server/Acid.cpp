//
// Created by cecix on 18/05/19.
//

#include "Acid.h"

Acid::Acid(b2Body* body):
        body(body) {
}

float Acid::getHorizontalPosition() {
    return this->body->GetPosition().x;
}

float Acid::getVerticalPosition() {
    return this->body->GetPosition().y;
}

