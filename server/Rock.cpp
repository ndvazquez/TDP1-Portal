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
#include "MetalBlock.h"
#include "Chell.h"
#include "Button.h"
#include <Box2D/Dynamics/b2World.h>


Rock::Rock(b2Body* body):
        Entity(rockType, body),
        dynamic(body) {
    this->actual_movement = new Stop(body);
    body->SetUserData(this);
}

void Rock::handleCollision(Entity *entity) {
    std::string type = entity->getType();
    if (type == "MetalBlock") {
/*        MetalBlock *metalBlock = static_cast<MetalBlock *>(entity);
        Coordinate *target = metalBlock->getOtherPortal();
        if (target != nullptr) {
            activateGravity();
            this->dynamic.teleport(target);
        }*/ // TODO: watch this
    }
    if (type == "Chell") {
        static_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == "Button") {
        Button* button = static_cast<Button*>(entity);
        float x_button = button->getHorizontalPosition();
        float x_rock = body->GetPosition().x;
        float delta = 0.1;
        if (x_rock > x_button - delta && x_rock < x_button + delta) {
            button->activate();
        }
    }
}

void Rock::elevate() {
    body->SetGravityScale(0);
    body->ApplyForce(b2Vec2(0, gameConfiguration.elevationForce),
            body->GetWorldCenter(), true);
}

void Rock::activateGravity() {
    body->SetGravityScale(1);
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

void Rock::teleport(Coordinate* target) {
    this->dynamic.teleport(target);
}
