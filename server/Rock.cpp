//
// Created by cecix on 17/05/19.
//

#define rockType "Rock"

#include <string>
#include <iostream>
#include "Rock.h"
#include "MoveRight.h"
#include "MoveLeft.h"
#include "Stop.h"
#include <Box2D/Dynamics/b2World.h>


Rock::Rock(b2Body* body):
        Entity(rockType, body),
        dynamic(body) {
    this->actual_movement = new Stop(body);
    body->SetUserData(this);
}

void Rock::handleCollision(Entity *entity) {
    std::string type = entity->getType();
}

void Rock::elevate() {
    body->SetGravityScale(0);
    body->ApplyForce(b2Vec2(0, gameConfiguration.elevationForce),
            body->GetWorldCenter(), true);
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
    body->SetLinearVelocity(b2Vec2(0, 0));
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

void Rock::downloadToEarth() {
    body->SetGravityScale(1);
}
