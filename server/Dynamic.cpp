//
// Created by cecix on 18/05/19.
//

#include <iostream>
#include <Box2D/Box2D.h>
#include "Dynamic.h"
#include "Entity.h"
#include "Coordinate.h"

Dynamic::Dynamic(b2Body* body):
        body(body) {
    float energy_ball_factor = gameConfiguration.energyBallImpulseFactor;
    this->energy_ball_impulse = body->GetMass() * energy_ball_factor;
}

void Dynamic::move(float force) {
}

void Dynamic::teleport(Coordinate* coordinate) {
    auto end = std::chrono::system_clock::now();
    auto difference = std::chrono::duration_cast<std::chrono::milliseconds>
            (end - timeStamp).count();
    if (difference <= 3000) return; //3 seconds to teletransport
    timeStamp = std::chrono::system_clock::now();

    float x = coordinate->getX();
    float y = coordinate->getY();
    body->SetTransform(b2Vec2(x, y), 0);
}

void Dynamic::moveRight(float force) {
    if (body->GetLinearVelocity().x > 0.5) force = 0;
    body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter(), true);
}

void Dynamic::moveLeft(float force) {
    if (body->GetLinearVelocity().x < -0.5) force = 0;
    body->ApplyForce(b2Vec2(-force, 0), body->GetWorldCenter(), true);
}

void Dynamic::stop(float force) {
    force = 0;
    body->ApplyForce(b2Vec2(force,0), body->GetWorldCenter(), true);
}

bool Dynamic::handleCollisions() {
    b2ContactEdge* edge = body->GetContactList();
    bool resul = false;
    size_t counter = 0;
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
        counter++;
    }
    return resul;
}

void Dynamic::flyHorizontal() {
    body->SetGravityScale(0);

    if (body->GetLinearVelocity().x != 0) return; //Already flying

    if (handleCollisions()) {
        energy_ball_impulse = -energy_ball_impulse;
        body->ApplyLinearImpulse(b2Vec2(energy_ball_impulse, 0),
                                 body->GetWorldCenter(), true);
    } else {
        body->ApplyLinearImpulse(b2Vec2(energy_ball_impulse, 0),
                                 body->GetWorldCenter(), true);
    }
}

void Dynamic::flyVertical() {
    body->SetGravityScale(0);

    if (body->GetLinearVelocity().y != 0) return; //Already flying

    if (handleCollisions()) {
        energy_ball_impulse = -energy_ball_impulse;
        body->ApplyLinearImpulse(b2Vec2(0, energy_ball_impulse),
                                 body->GetWorldCenter(), true);
    } else {
        body->ApplyLinearImpulse(b2Vec2(0, energy_ball_impulse),
                                 body->GetWorldCenter(), true);
    }
}

void Dynamic::adjustJump() {
    b2World* world = body->GetWorld();
    float gravity_jump = gameConfiguration.gravityJump;
    world->SetGravity(b2Vec2(0, gravity_jump));
}

bool Dynamic::jump(bool chellFloor) {
    adjustJump();

    float epsilon = pow(10.5, -9);
    bool chell_is_still = body->GetLinearVelocity().y < epsilon
                        && body->GetLinearVelocity().y > -epsilon;

    if (! chell_is_still && ! chellFloor) return false;

    float initialVelocity = gameConfiguration.chellInitialVelocity;
    float impulse = body->GetMass() * initialVelocity;
    body->ApplyLinearImpulse(b2Vec2(0,impulse), body->GetWorldCenter() , true);
    return true;
}


Dynamic::~Dynamic() {
}
