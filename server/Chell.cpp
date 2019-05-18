//
// Created by cecix on 18/05/19.
//

#include "Chell.h"

Chell::Chell(b2Body* body):
        dynamic(body) {
    this->actual_movement = 0;
}

float Chell::getHorizontalPosition() {
    return this->dynamic.getHorizontalPosition();
}

float Chell::getVerticalPosition() {
    return this->dynamic.getVerticalPosition();
}

void Chell::moveRight() {
    this->actual_movement = 1;
}

void Chell::moveLeft() {
    this->actual_movement = 2;
}

void Chell::stop() {
    this->actual_movement = 0;
}


float Chell::getHorizontalVelocity() {
    return this->dynamic.getHorizontalVelocity();
}

float Chell::getVerticalVelocity() {
    return this->dynamic.getVerticalVelocity();
}

void Chell::update() {
    if (this->actual_movement == 1) this->dynamic.moveRight();
    if (this->actual_movement == 2) this->dynamic.moveLeft();
    else this->dynamic.stop();
};