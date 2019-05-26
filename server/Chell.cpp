//
// Created by cecix on 18/05/19.
//

#define chellType "Chell"

#include <iostream>
#include "Chell.h"
#include "MoveRight.h"
#include "Stop.h"
#include "MoveLeft.h"
#include "../editor/Chell.h"

Chell::Chell(b2Body* body):
        Entity(chellType),
        dynamic(body) {
    this->body = body;
    this->actual_movement = new Stop(body);
    body->SetUserData(this);
    chell_is_on_floor = true;
    rock = nullptr;
}

void Chell::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    chell_is_on_floor = type == "MetalBlock" || type == "BrickBlock"
                        || type == "DiagonalMetalBlock" || type == "Floor";
}

void Chell::grabRock(Rock* rock) {
    this->rock = rock;
}

void Chell::downloadRock() {
    if (! rock) return;
    rock->downloadToEarth();
    rock = nullptr;
}

void Chell::onFloor(bool onFloor) {
    chell_is_on_floor = onFloor;
}

void Chell::moveRight() {
    destroyActualMovement();
    this->actual_movement = new MoveRight(body);
    if (this->rock) rock->moveRight();
}

void Chell::moveLeft() {
    destroyActualMovement();
    this->actual_movement = new MoveLeft(body);
    if (this->rock) rock->moveLeft();
}

void Chell::stop() {
    destroyActualMovement();
    this->actual_movement = new Stop(body);
    if (this->rock) rock->stop();
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
    this->actual_movement->move(gameConfiguration.chellForce);
    if (this->rock) rock->update();
}

void Chell::jump() {
    bool resul = this->dynamic.jump(chell_is_on_floor);
    if (resul) chell_is_on_floor = false;
}

bool Chell::inGround() {
    float epsilon = pow(10, -7);
    bool chell_is_still = body->GetLinearVelocity().y < epsilon && body->GetLinearVelocity().y > -epsilon;
    if (chell_is_still) dynamic.handleCollisions();
    return chell_is_on_floor;
}

Chell::~Chell() {
    destroyActualMovement();
}
