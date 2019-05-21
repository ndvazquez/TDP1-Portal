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

void Dynamic::moveRight() {
    float force = 15; //TODO: change this harcoded variable
    if (body->GetLinearVelocity().x > 0.5) force = 0;
    body->ApplyForce(b2Vec2(force,0), body->GetWorldCenter(), true);
}

void Dynamic::moveLeft() {
    float force = -15; //TODO: change this harcoded variable
    if (body->GetLinearVelocity().x < -0.5) force = 0;
    body->ApplyForce(b2Vec2(force,0), body->GetWorldCenter(), true);
}

void Dynamic::stop() {
    float force = 0;
    body->ApplyForce(b2Vec2(force,0), body->GetWorldCenter(), true);
}

float Dynamic::getHorizontalPosition() {
    return body->GetPosition().x;
}

float Dynamic::getVerticalPosition() {
    return body->GetPosition().y;
}

void Dynamic::jump() {
    float epsilon = pow(10, -9);
    if (body->GetLinearVelocity().y > epsilon || body->GetLinearVelocity().y < -epsilon) return;

    float impulse = body->GetMass() * 4;
    body->ApplyLinearImpulse(b2Vec2(0,impulse), body->GetWorldCenter() , true);
}

float Dynamic::getHorizontalVelocity() {
    return body->GetLinearVelocity().x;
}

float Dynamic::getVerticalVelocity() {
    return body->GetLinearVelocity().y;
}

Dynamic::~Dynamic() {
}
