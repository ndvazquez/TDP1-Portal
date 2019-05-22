//
// Created by cecix on 18/05/19.
//

#include "Chell.h"
#include "MoveRight.h"
#include "Stop.h"
#include "MoveLeft.h"
#include "../editor/Chell.h"


Chell::Chell(b2Body* body):
        dynamic(body) {
    this->body = body;
    this->actual_movement = new Stop(body);
}

void Chell::moveRight() {
    destroyActualMovement();
    this->actual_movement = new MoveRight(body);
}

void Chell::moveLeft() {
    destroyActualMovement();
    this->actual_movement = new MoveLeft(body);
}

void Chell::stop() {
    destroyActualMovement();
    this->actual_movement = new Stop(body);
}

void Chell::destroyActualMovement() {
    delete this->actual_movement;
}

void Chell::update() {
    this->actual_movement->move(chellForce);
}

void Chell::jump() {
    this->dynamic.jump();
}

float Chell::getHorizontalPosition() {
    return this->dynamic.getHorizontalPosition();
}

float Chell::getVerticalPosition() {
    return this->dynamic.getVerticalPosition();
}

float Chell::getHorizontalVelocity() {
    return this->dynamic.getHorizontalVelocity();
}

float Chell::getVerticalVelocity() {
    return this->dynamic.getVerticalVelocity();
}

Chell::~Chell() {
    destroyActualMovement();
}
