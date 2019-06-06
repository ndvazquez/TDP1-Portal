//
// Created by cecix on 17/05/19.
//

#define rockType "Rock"

#include <string>
#include "Rock.h"
#include "MoveRight.h"
#include "MoveLeft.h"
#include "Stop.h"
#include "Chell.h"

Rock::Rock(b2Body* body):
        Entity(rockType, body),
        dynamic(body) {
    this->actual_movement = new Stop(body);
    body->SetUserData(this);
    this->on_floor = false;
}

void Rock::handleCollision(Entity *entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        Chell* chell = static_cast<Chell*>(entity);
        if (body->GetLinearVelocity().y < 0 && ! on_floor) {
            chell->die();
        } else {
            stop();
        }
        makeStatic();
    }
    if (type == "MetalBlock" || type == "BrickBlock" || type == "Floor") {
        on_floor = true;
    }
}

void Rock::elevate() {
    float x_floor = body->GetPosition().x;
    float y_floor = body->GetPosition().y;
    body->SetTransform(b2Vec2(x_floor, y_floor + 1), 0);
}

void Rock::makeStatic() {
    body->SetType(b2_staticBody);
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
    makeDynamic();
}

bool Rock::isOnFloor() {
    return on_floor;
}

bool Rock::onFloor(bool onFloor) {
    this->on_floor = onFloor;
}

void Rock::downloadToEarth() {
    body->SetGravityScale(0);
    this->dynamic.downloadToEarth();
}
