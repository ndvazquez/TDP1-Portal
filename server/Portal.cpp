//
// Created by cecix on 6/06/19.
//

#include <iostream>
#include "Portal.h"
#include "Chell.h"

#define portalType "Portal"

Portal::Portal(b2Body* body, Coordinate* target):
    Entity(portalType, body) {
    this->target = target;
    this->body->SetUserData(this);
}

void Portal::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        Chell* chell = static_cast<Chell*>(entity);
        if (target != nullptr) chell->teleport(target);
    }
}

Coordinate* Portal::getTarget() {
    return target;
}

Portal::~Portal() {
    if (target != nullptr) delete target;
}
