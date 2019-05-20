//
// Created by cecix on 17/05/19.
//

#include "Rock.h"

Rock::Rock(b2Body* body):
    dynamic(body) {
}

float Rock::getHorizontalPosition() {
    return this->dynamic.getHorizontalPosition();
}

float Rock::getVerticalPosition() {
    return this->dynamic.getVerticalPosition();
}

float Rock::getVerticalVelocity() {
    return this->dynamic.getVerticalVelocity();
}

float Rock::getHorizontalVelocity() {
    return this->dynamic.getHorizontalVelocity();
}

void Rock::move() {
    this->dynamic.moveRock();
}