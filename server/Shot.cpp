//
// Created by cecix on 3/06/19.
//

#include "Shot.h"

#include <string>
#include <Box2D/Dynamics/b2World.h>

Shot::Shot(std::string type, b2Body *body, Chell* chell, Coordinate* target) :
        Entity(type, body) {
    this->chell = chell;
    this->target = target;
    //body->SetUserData(this); //TODO: cambiar
    this->is_dead = false;
}

Chell* Shot::getChell() {
    return chell;
}

void Shot::handleCollision(Entity* entity) {
}


void Shot::setExactPosition() {
    float target_x = target->getX();
    float target_y = target->getY();
    body->SetTransform(b2Vec2(target_x, target_y), 0);
}

void Shot::shoot() {
    b2World* world = body->GetWorld();
    world->SetGravity(b2Vec2(0, 0));

    float origin_x = body->GetPosition().x;
    float origin_y = body->GetPosition().y;
    float target_x = target->getX();
    float target_y = target->getY();

    float to_advance_x = target_x - origin_x;
    float to_advance_y = target_y - origin_y;

    if (to_advance_x <= 0.001) to_advance_x = 0;
    if (to_advance_y <= 0.001) to_advance_y = 0;

    float velocity_x = body->GetMass() * to_advance_x;
    float velocity_y = body->GetMass() * to_advance_y;

    if (to_advance_x == 0 && to_advance_y == 0) {
        body->SetLinearVelocity(b2Vec2(0, 0));
        setExactPosition();
        this->is_dead = true;
        return;
    }

    b2Vec2 velocity(velocity_x, velocity_y);
    body->ApplyLinearImpulse(velocity, body->GetWorldCenter(), true);
}

bool Shot::isDead() {
    return is_dead;
}
