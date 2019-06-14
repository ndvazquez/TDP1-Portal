//
// Created by cecix on 3/06/19.
//

#include "Shot.h"

#include <string>
#include <Box2D/Dynamics/b2World.h>
#include <iostream>

Shot::Shot(std::string type, b2Body *body, Chell* chell, Coordinate* target) :
        Entity(type, body), dynamic(body) {
    this->chell = chell;
    this->target = target;
    this->is_dead = false;
    this->origin = new Coordinate(body->GetPosition().x, body->GetPosition().y);
}

Chell* Shot::getChell() {
    return chell;
}

void Shot::handleCollision(Entity* entity) {
}

void Shot::die() {
    this->is_dead = true;
}

void Shot::shoot() {
    chell->stop();
    float delta = 0.5;

    b2World* world = body->GetWorld();
    world->SetGravity(b2Vec2(0, 0));

    this->dynamic.handleCollisions();

    float origin_x = origin->getX();
    float origin_y =  origin->getY();
    float target_x = target->getX();
    float target_y = target->getY();

    float to_advance_x = target_x - origin_x;
    float to_advance_y = target_y - origin_y;

    float velocity_x = to_advance_x * 3;
    float velocity_y = to_advance_y * 3;

    float x_act = body->GetPosition().x;
    float y_act = body->GetPosition().y;

    bool x_done = (x_act >= target_x - delta && x_act <= target_x + delta);
    bool y_done = (y_act >= target_y - delta && y_act <= target_y + delta);

    if (x_done) velocity_x = 0;

    if (y_done) velocity_y = 0;

    body->SetLinearVelocity(b2Vec2(velocity_x, velocity_y));

    if (x_done && y_done) {
        die();
        return;
    }
}

bool Shot::isDead() {
    return is_dead;
}
