//
// Created by cecix on 6/06/19.
//

#include <string>
#include <iostream>
#include "Portal.h"
#include "Chell.h"
#include "EnergyBall.h"
#include "BlueShot.h"
#include "OrangeShot.h"

#define portalType "Portal"

Portal::Portal(b2Body* body, Coordinate* target,
        PortalOrientation orientation, PortalType type):
    Entity(portalType, body) {
    this->target = target;
    this->body->SetUserData(this);
    this->orientation = orientation;
    this->type = type;
}

void Portal::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        Chell* chell = static_cast<Chell*>(entity);
        if (target != nullptr) {
            chell->teleport(target, getPortalType());
        }
    }
    if (type == "Rock") {
        Rock* rock = static_cast<Rock*>(entity);
        if (target != nullptr)  {
            rock->teleport(target, getPortalType());
            rock->activateGravity();
        }
    }
    if (type == "EnergyBall") {
        EnergyBall* eb = static_cast<EnergyBall*>(entity);
        if (target != nullptr) {
            eb->teleport(target, getPortalType());
        }
    }
    if (type == "BlueShot") {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == "OrangeShot") {
        static_cast<OrangeShot*>(entity)->die();
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

PortalType Portal::getPortalType() {
    return type;
}

Portal::~Portal() {
    if (target != nullptr) delete target;
}
