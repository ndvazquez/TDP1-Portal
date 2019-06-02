//
// Created by cecix on 1/06/19.
//

#include <iostream>
#include "Portal.h"
#include "Chell.h"

#define portalType "Portal"

Portal::Portal(b2Body* body):
        Entity(portalType),
        body(body) {
    body->SetUserData(this);
}

float Portal::getHorizontalPosition() {
    return this->body->GetPosition().x;
}

float Portal::getVerticalPosition() {
    return this->body->GetPosition().y;
}

void Portal::addOtherPortal(Coordinate* coordinate) {
    this->other_portal = coordinate;
}

void Portal::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "MetalBlock" || type == "DiagonalMetalBlock") {
        //se puede hacer un portal
    }
    if (type == "BrickBlock") {
        //no se puede hacer un portal
    }
    if (type == "Chell") {
        static_cast<Chell*>(entity)->teleport(other_portal);
    }
}

Coordinate* Portal::getOtherPortal() {
    return other_portal;
}
