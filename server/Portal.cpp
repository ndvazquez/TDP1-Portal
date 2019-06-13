//
// Created by cecix on 6/06/19.
//

#include <string>
#include <iostream>
#include "Portal.h"
#include "Chell.h"
#include "EnergyBall.h"

#define portalType "Portal"

Portal::Portal(b2Body* body, Coordinate* target,
        PortalOrientation orientation):
    Entity(portalType, body) {
    this->target = target;
    this->body->SetUserData(this);
    this->orientation = orientation;
}

void Portal::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        Chell* chell = static_cast<Chell*>(entity);
        if (target != nullptr) chell->teleport(target);
    }
    if (type == "Rock") {
        Rock* rock = static_cast<Rock*>(entity);
        if (target != nullptr)  {
            rock->teleport(target);
            rock->activateGravity();
        }
    }
    if (type == "EnergyBall") {
        EnergyBall* eb = static_cast<EnergyBall*>(entity);
        if (target != nullptr) {
            eb->teleport(target);
        }
    }
}

Coordinate* Portal::getTarget() {
    return target;
}

PortalOrientation Portal::getOrientation() {
    return orientation;
}

void Portal::addTarget(Coordinate* target) {
    this->target = target;
}

Portal::~Portal() {
    if (target != nullptr) delete target;
}
