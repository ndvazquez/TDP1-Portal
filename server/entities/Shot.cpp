#include <utility>

//
// Created by cecix on 3/06/19.
//

#include "Shot.h"

#define PI 3.14159265

#include <math.h>
#include <string>
#include <Box2D/Dynamics/b2World.h>
#include <iostream>

Shot::Shot(std::string type, b2Body *body, Chell* chell, Coordinate* target) :
        Entity(std::move(type), body), dynamic(body) {
    this->chell = chell;
    this->target = target;
    this->is_dead = false;
    this->origin = new Coordinate(body->GetPosition().x, body->GetPosition().y);
    this->angle = 0;
}

Shot::~Shot() {
    delete origin;
    delete target;
}

Chell* Shot::getChell() {
    return chell;
}

float Shot::getAngle() {
    return angle;
}

void Shot::handleCollision(Entity* entity) {
}

void Shot::die() {
    this->is_dead = true;
}

void Shot::shoot() {
    float delta = 0.5;

    body->SetGravityScale(0);

    this->dynamic.handleCollisions();

    float origin_x = origin->getX();
    float origin_y =  origin->getY();
    float target_x = target->getX();
    float target_y = target->getY();

    float x_act = body->GetPosition().x;
    float y_act = body->GetPosition().y;

    bool x_done = (x_act >= target_x - delta && x_act <= target_x + delta);
    bool y_done = (y_act >= target_y - delta && y_act <= target_y + delta);

    float to_advance_x = target_x - origin_x;
    float to_advance_y = target_y - origin_y;

    float opposite = target_y - origin_y;
    if (opposite < 0) opposite = -opposite;
    float adyacent = target_x - origin_x;
    if (adyacent < 0) adyacent = -adyacent;

    this->angle = atan(opposite/adyacent) * 180 / PI;

    if (to_advance_x < 0 && to_advance_y > 0) { //2d quarter
        this->angle += 90;
    } else if (to_advance_x < 0 && to_advance_y < 0) { //3er quarter
        this->angle += 90*2;
    } else if (to_advance_x > 0 && to_advance_y < 0) { //4to quarter
        this->angle += 90*3;
    }

    b2Vec2 velocity (to_advance_x, to_advance_y);
    velocity.Normalize();
    velocity.x *= gameConfiguration.shotFactor;
    velocity.y *= gameConfiguration.shotFactor;

    if (x_done) velocity.x = 0;

    if (y_done) velocity.y = 0;

    body->SetLinearVelocity(velocity);

    if (x_done && y_done) die();
}

bool Shot::isDead() {
    return is_dead;
}
