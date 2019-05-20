//
// Created by cecix on 18/05/19.
//

#include <iostream>
#include <Box2D/Box2D.h>
#include "Dynamic.h"
#include "Entity.h"

Dynamic::Dynamic(b2Body* body):
        body(body) {
    impulse = body->GetMass() * 50;
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

void Dynamic::jump() {
    if (body->GetLinearVelocity().y != 0) return; //Shouldn't jump twice
    float impulse = body->GetMass() * 4;
    body->ApplyLinearImpulse(b2Vec2(0,impulse), body->GetWorldCenter() , true);
}

bool Dynamic::isColliding() {
    b2ContactEdge* edge = body->GetContactList();
    while (edge != NULL) {
        b2Contact* contact = edge->contact;
        if (contact->IsTouching()) return true;
        edge = edge->next;
    }
    return false;
}

bool Dynamic::handleCollisions() {
    b2ContactEdge* edge = body->GetContactList();
    bool resul = false;
    while (edge != NULL) {
        b2Contact* contact = edge->contact;
        if (contact->IsTouching()) {
            void* user_A = contact->GetFixtureA()->GetBody()->GetUserData();
            void* user_B = contact->GetFixtureB()->GetBody()->GetUserData();
            if (user_A != NULL && user_B != NULL) {
                Entity* entity_A = static_cast<Entity*>(user_A);
                Entity* entity_B = static_cast<Entity*> (user_B);
                entity_A->handleCollision(entity_B);
            }
            resul = true;
        }
        edge = edge->next;
    }
    return resul;
}

void Dynamic::flyHorizontal() {
    //Eliminate gravity
    float mass = body->GetMass();
    float gravity = -1;
    float force_y = - (mass * gravity);
    body->ApplyForce(b2Vec2(0, force_y), body->GetWorldCenter(), true);

    if (body->GetLinearVelocity().x != 0) return; //Already flying

    if (handleCollisions()) {
        impulse = -impulse;
        body->ApplyLinearImpulse(b2Vec2(impulse, 0),
                body->GetWorldCenter(), true);
    } else {
        body->ApplyLinearImpulse(b2Vec2(impulse, 0),
                body->GetWorldCenter(), true);
    }
}

void Dynamic::flyVertical() {
    //Eliminate gravity
    float mass = body->GetMass();
    float gravity = -1;
    float force_y = - (mass * gravity);
    body->ApplyForce(b2Vec2(0, force_y), body->GetWorldCenter(), true);

    if (body->GetLinearVelocity().y != 0) return; //Already flying

    if (handleCollisions()) {
        impulse = -impulse;
        body->ApplyLinearImpulse(b2Vec2(0, impulse),
                                 body->GetWorldCenter(), true);
    } else {
        body->ApplyLinearImpulse(b2Vec2(0, impulse),
                                 body->GetWorldCenter(), true);
    }
}

float Dynamic::getHorizontalPosition() {
    return body->GetPosition().x;
}

float Dynamic::getVerticalPosition() {
    return body->GetPosition().y;
}

float Dynamic::getHorizontalVelocity() {
    return body->GetLinearVelocity().x;
}

float Dynamic::getVerticalVelocity() {
    return body->GetLinearVelocity().y;
}

Dynamic::~Dynamic() {
}
