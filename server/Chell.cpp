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

void Chell::update() {
    this->actual_movement->move(chellForce);
}

void Chell::jump(float y0) {
    this->dynamic.jump(y0);
}

bool Chell::inGround(float y0) {
    float epsilon = pow(10.5, -9);
    // This is probably a constant or something else, but I had to rename it
    float deltaGround = 0.05;

    bool chell_is_still = body->GetLinearVelocity().y < epsilon && body->GetLinearVelocity().y > -epsilon;
    bool chell_is_in_floor = body->GetPosition().y <= y0 + deltaGround;

    if (! chell_is_still && ! chell_is_in_floor) return false; //can't jump because chell is in movement
    return true;
}

Chell::~Chell() {
    destroyActualMovement();
}