//
// Created by cecix on 17/05/19.
//

#define rockType "Rock"

#include <iostream>
#include "Rock.h"
#include "MoveRight.h"
#include "MoveLeft.h"
#include "Stop.h"
#include "Chell.h"

Rock::Rock(b2Body* body):
        Entity(rockType),
        dynamic(body) {
    this->body = body;
    this->actual_movement = new Stop(body);
    body->SetUserData(this);
}

void Rock::handleCollision(Entity *entity) {
    if (entity->getType() == "Chell") {
        std::cout << "omg a chell" << std::endl;
        Chell* chell = static_cast<Chell*>(entity);
        if (body->GetLinearVelocity().y < 0) chell->die();
        else stop();
    }
}

void Rock::makeDynamic() {
    body->SetType(b2_dynamicBody);
    body->SetAwake(true);
}

void Rock::moveRight() {
    destroyActualMovement();
    this->actual_movement = new MoveRight(body);
}

void Rock::moveLeft() {
    destroyActualMovement();
    this->actual_movement = new MoveLeft(body);
}

void Rock::stop() {
    destroyActualMovement();
    this->actual_movement = new Stop(body);
}

void Rock::destroyActualMovement() {
    delete this->actual_movement;
}

void Rock::update() {
    dynamic.handleCollisions();
    this->actual_movement->move(gameConfiguration.rockForce);
}

void Rock::eliminateGravity() {
    this->dynamic.eliminateGravity();
}

void Rock::downloadToEarth() {
    body->SetType(b2_staticBody);
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