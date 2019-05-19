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
    float force = 1000; //TODO: change this harcoded variable
    body->ApplyForce(b2Vec2(force,0), body->GetWorldCenter(), true);
}

void Dynamic::moveLeft() {
    float force = -1000; //TODO: change this harcoded variable
    body->ApplyForce(b2Vec2(force,0), body->GetWorldCenter(), true);
}

void Dynamic::stop() {
    float force = 0;
    body->ApplyForce(b2Vec2(force,0), body->GetWorldCenter(), true);
}

void Dynamic::jump() {
    float impulse = body->GetMass() * 10;
    body->ApplyLinearImpulse(b2Vec2(0,impulse), body->GetWorldCenter() , true);
}

float Dynamic::getHorizontalVelocity() {
    return body->GetLinearVelocity().x;
}

float Dynamic::getVerticalVelocity() {
    return body->GetLinearVelocity().y;
}
/*
bool Dynamic::isColliding() {
    for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next){
        return true;
    }
    return false;
}


void Dynamic::fly(float velocity) {
    float impulse = body->GetMass() * velocity;
    body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);
    if (isColliding()) {
        stop();
        body->ApplyLinearImpulse(b2Vec2(0, -impulse), body->GetWorldCenter(), true); //TODO: vertical collisions
    }
}

*/
Dynamic::~Dynamic() {
}
