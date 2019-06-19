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

Portal::Portal(b2Body* body, Coordinate* target,
        PortalOrientation orientation, PortalType type):
    Entity(PORTAL_NAME, body) {
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

    if (type == CHELL_NAME) {
        Chell* chell = static_cast<Chell*>(entity);
        if (target != nullptr) {
            chell->teleport(target, portal_type_target);
        }
    }
    if (type == ROCK_NAME) {
        Rock* rock = static_cast<Rock*>(entity);
        if (target != nullptr)  {
            rock->teleport(target, portal_type_target);
        }
    }
    if (type == EB_NAME) {
        EnergyBall* eb = static_cast<EnergyBall*>(entity);
        if (target != nullptr) {
            eb->teleport(target, portal_type_target);
        }
    }
    if (type == BLUE_SHOT_NAME) {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
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
    if (this->target != nullptr) delete this->target;
    this->target = target;
}

Portal::~Portal() {
    std::cout << "llamo a este bello destructor" << std::endl;
    if (target != nullptr) delete target;
}
