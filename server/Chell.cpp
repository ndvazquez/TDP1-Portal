//
// Created by cecix on 18/05/19.
//

#define chellType "Chell"

#include <string>
#include "Chell.h"
#include "MoveRight.h"
#include "Stop.h"
#include "MoveLeft.h"
#include "../editor/Chell.h"
#include "Rock.h"

Chell::Chell(b2Body* body):
        Entity(chellType),
        dynamic(body) {
    this->body = body;
    this->actual_movement = new Stop(body);
    this->actual_state = IDLE;
    body->SetUserData(this);
    chell_is_on_floor = true;
    dead = false;
    rock = nullptr;
}

void Chell::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Rock") {
        Rock* rock = static_cast<Rock*>(entity);
        if (rock->getVerticalVelocity() < -0 && ! rock->isOnFloor()) {
            die();
        }
        rock->makeStatic();
    }

    if (type == "Acid" || type == "EnergyBall") {
        die();
    }

    chell_is_on_floor = type == "MetalBlock" || type == "BrickBlock"
                        || type == "DiagonalMetalBlock" || type == "Floor";
}

void Chell::die() {
    //this->actual_state = DEAD;
    dead = true;
}

bool Chell::isDead() {
    return dead;
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
    if (!this->actual_state == JUMPING) this->actual_state = MOVING_RIGHT;
    if (this->rock) rock->moveRight();
}

void Chell::moveLeft() {
    destroyActualMovement();
    this->actual_movement = new MoveLeft(body);
    if (!this->actual_state == JUMPING) this->actual_state = MOVING_LEFT;
    if (this->rock) rock->moveLeft();
}

void Chell::stop() {
    destroyActualMovement();
    this->actual_movement = new Stop(body);
    if (! chell_is_on_floor) this->actual_state = JUMPING;
    else this->actual_state = IDLE;
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
    chell_is_on_floor = inGround();
    if (chell_is_on_floor) this->dynamic.handleCollisions();
    this->actual_movement->move(gameConfiguration.chellForce);
    if (this->rock) rock->update();
}

void Chell::jump() {
    bool resul = this->dynamic.jump(chell_is_on_floor);
    if (resul) {
        actual_state = JUMPING;
        chell_is_on_floor = false;
    }
}

bool Chell::inGround() {
    float epsilon = pow(10, -7);
    bool chell_is_still = body->GetLinearVelocity().y < epsilon
                        && body->GetLinearVelocity().y > -epsilon;
    if (chell_is_still) dynamic.handleCollisions();
    return chell_is_on_floor;
}

State Chell::getState() {
    return actual_state;
}

Chell::~Chell() {
    destroyActualMovement();
}
