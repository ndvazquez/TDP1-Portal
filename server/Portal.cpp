//
// Created by cecix on 1/06/19.
//

#include <string>
#include "Portal.h"
#include "Chell.h"

#define portalType "Portal"

Portal::Portal(b2Body* body):
    Entity(portalType, body) {
    body->SetUserData(this);
    other_portal = nullptr;
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
