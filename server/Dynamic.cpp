//
// Created by cecix on 18/05/19.
//

#include <iostream>
#include "Dynamic.h"

Dynamic::Dynamic(b2Body* body):
    body(body) {
}

void Dynamic::move() {
}

float Dynamic::getHorizontalPosition() {
    return body->GetPosition().x;
}

float Dynamic::getVerticalPosition() {
    return body->GetPosition().y;
}

void Dynamic::moveRight() {
    float force = 15; //TODO: change this harcoded variable
    body->ApplyForce(b2Vec2(force,0), body->GetWorldCenter(), true);
}

void Dynamic::moveLeft() {
    float force = -15; //TODO: change this harcoded variable
    body->ApplyForce(b2Vec2(force,0), body->GetWorldCenter(), true);
}

void Dynamic::stop() {
    float force = 0;
    body->ApplyForce(b2Vec2(force,0), body->GetWorldCenter(), true);
}

float Dynamic::getHorizontalVelocity() {
    return body->GetLinearVelocity().x;
}

float Dynamic::getVerticalVelocity() {
    return body->GetLinearVelocity().y;
}

Dynamic::~Dynamic() {
}
