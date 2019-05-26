//
// Created by cecix on 17/05/19.
//

#include <iostream>
#include "Rock.h"
#include "MoveRight.h"
#include "MoveLeft.h"
#include "Stop.h"
#include "MoveUp.h"
#include "MoveDown.h"

Rock::Rock(b2Body* body):
    dynamic(body) {
    this->body = body;
    this->actual_movement = new Stop(body);
}

void Rock::moveRight() {
    destroyActualMovement();
    this->actual_movement = new MoveRight(body);
}

void Rock::moveLeft() {
    destroyActualMovement();
    this->actual_movement = new MoveLeft(body);
}

void Rock::moveUp() {
    destroyActualMovement();
    this->actual_movement = new MoveUp(body);
}

void Rock::moveDown() {
    destroyActualMovement();
    this->actual_movement = new MoveDown(body);
}

void Rock::stop() {
    destroyActualMovement();
    this->actual_movement = new Stop(body);
}

void Rock::destroyActualMovement() {
    delete this->actual_movement;
}

void Rock::update() {
    eliminateGravity();
    this->actual_movement->move(gameConfiguration.rockForce);
}

void Rock::eliminateGravity() {
    this->dynamic.eliminateGravity();
}

void Rock::downloadToEarth() {
    eliminateGravity();
    this->dynamic.downloadToEarth();
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
