//
// Created by cecix on 18/05/19.
//

#include "Chell.h"

Chell::Chell(b2Body* body):
        dynamic(body) {
}

float Chell::getHorizontalPosition() {
    return this->dynamic.getHorizontalPosition();
}

float Chell::getVerticalPosition() {
    return this->dynamic.getVerticalPosition();
}

void Chell::moveRight() {
    this->dynamic.moveRight();
}

void Chell::moveLeft() {
    this->dynamic.moveLeft();
}

void Chell::stop() {
    this->dynamic.stop();
}


float Chell::getHorizontalVelocity() {
    return this->dynamic.getHorizontalVelocity();
}

float Chell::getVerticalVelocity() {
    return this->dynamic.getVerticalVelocity();
}
