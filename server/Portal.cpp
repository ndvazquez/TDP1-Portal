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
    this->portal_type_target = type;
}

PortalType Portal::getPortalType() {
    return portal_type_target;
}

void Portal::addPortalType(PortalType type) {
    this->portal_type_target = type;
}

void Portal::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        Chell* chell = static_cast<Chell*>(entity);
        if (target != nullptr) {
            chell->teleport(target, portal_type_target);
        }
    }
    if (type == "Rock") {
        Rock* rock = static_cast<Rock*>(entity);
        if (target != nullptr)  {
            rock->teleport(target, portal_type_target);
        }
    }
    if (type == "EnergyBall") {
        EnergyBall* eb = static_cast<EnergyBall*>(entity);
        if (target != nullptr) {
            eb->teleport(target, portal_type_target);
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

Portal::~Portal() {
    if (target != nullptr) delete target;
}
