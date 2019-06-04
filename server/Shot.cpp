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

    float frequency = 60;
    float velocity_x = to_advance_x * frequency;
    float velocity_y = to_advance_y * frequency;

    float x_act = body->GetPosition().x;
    float y_act = body->GetPosition().y;
    
    //Always right. Hyper harcoded
    if (x_act >= target_x - delta && x_act <= target_x + delta &&
        y_act >= target_y - delta && y_act <= target_y + delta) {
        body->SetLinearVelocity(b2Vec2(0, 0));
        die();
        return;
    }

    if (body->GetLinearVelocity(). y != 0 || body->GetLinearVelocity().x != 0) {
        return;
    }

    body->SetLinearVelocity(b2Vec2(velocity_x, velocity_y));
}

bool Shot::isDead() {
    return is_dead;
}
