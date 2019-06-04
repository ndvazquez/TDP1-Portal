//
// Created by cecix on 2/06/19.
//

#define blueShotType "BlueShot"

#include <string>

#include <Box2D/Dynamics/b2World.h>
#include <iostream>
#include "BlueShot.h"
#include "MetalBlock.h"
#include "DiagonalMetalBlock.h"


BlueShot::BlueShot(b2Body *body, Chell* chell, Coordinate* target) :
    Entity(blueShotType, body) {
    this->chell = chell;
    this->target = target;
    body->SetUserData(this);
    this->is_dead = false;
}

void BlueShot::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "MetalBlock") {

        /*MetalBlock* metalBlock = static_cast<MetalBlock*>(entity);
        metalBlock->createBluePortal();
        Coordinate* portalCoordinates = new Coordinate(metalBlock->getHorizontalPosition(),
                                        metalBlock->getVerticalPosition());
        chell->addBluePortal(portalCoordinates);*/
    }
    if (type == "DiagonalMetalBlock") {

       /* DiagonalMetalBlock* diagonalBlock =static_cast<DiagonalMetalBlock*>(entity);
        diagonalBlock->createBluePortal();
        float x_portal_coordinates = diagonalBlock->getHorizontalPosition();
        float y_portal_coordinates = diagonalBlock->getVerticalPosition();
        Coordinate* portalCoordinates = new Coordinate(x_portal_coordinates,
                                                       y_portal_coordinates);
        chell->addBluePortal(portalCoordinates);*/
    }
}

Chell* BlueShot::getChell() {
    return chell;
}

void BlueShot::setExactPosition() {
    float target_x = target->getX();
    float target_y = target->getY();
    body->SetTransform(b2Vec2(target_x, target_y), 0);
}

void BlueShot::shoot() {
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

bool BlueShot::isDead() {
    return is_dead;
}



