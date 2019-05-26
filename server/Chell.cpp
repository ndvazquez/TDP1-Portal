//
// Created by cecix on 18/05/19.
//

#define chellType "Chell"

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
    dead = false;
}

void Chell::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "MetalBlock" || type == "BrickBlock"
            || type == "DiagonalMetalBlock" || type == "Floor") {
        chell_is_on_floor = true;
    }
    if (type == "Acid") {
        die();
    }
}

void Chell::die() {
    dead = true;
}

bool Chell::isDead() {
    return dead;
}

void Chell::onFloor(bool onFloor) {
    chell_is_on_floor = onFloor;
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
    this->dynamic.handleCollisions();
    this->actual_movement->move(gameConfiguration.chellForce);
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
