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
    b2World* world = body->GetWorld();
    world->SetGravity(b2Vec2(0, 0));

    this->dynamic.handleCollisions();

    if (body->GetLinearVelocity(). y != 0 && body->GetLinearVelocity().x != 0) {
        //body->SetLinearVelocity(b2Vec2(0,0));
        //this->to_be_dead = true;
        return;
    }
    if (to_be_dead) return;

    float origin_x = origin->getX();
    float origin_y =  origin->getY();
    float target_x = target->getX();
    float target_y = target->getY();

    float to_advance_x = target_x - origin_x;
    float to_advance_y = target_y - origin_y;

    float x_act = body->GetPosition().x;
    float y_act = body->GetPosition().y;

    float frequency = 60;
    float velocity_x = to_advance_x * frequency * body->GetMass();
    float velocity_y = to_advance_y * frequency * body->GetMass();

    body->SetLinearVelocity(b2Vec2(velocity_x, velocity_y));

    /*
    float velocity_x = body->GetMass() * to_advance_x;
    float velocity_y = body->GetMass() * to_advance_y;

    if (to_be_dead && counter > 2) {
        std::cout << "muri" << std::endl;
        this->is_dead = true;
        return;
    }

    if (((x_act >= target_x && x_act > origin_x) || (x_act <= target_x && x_act < origin_x)) &&
    ((y_act >= target_y  && y_act > origin_y) || (y_act <= target_y && y_act < origin_y))) {
        body->SetLinearVelocity(b2Vec2(0, 0));
        setExactPosition();
        this->to_be_dead = true;
        counter++;
        return;
    }

    if (body->GetLinearVelocity().x != 0 && body->GetLinearVelocity().y != 0) return;

    b2Vec2 velocity(velocity_x, velocity_y);
    body->ApplyLinearImpulse(velocity, body->GetWorldCenter(), true);
     */
}

bool Shot::isDead() {
    return is_dead;
}
