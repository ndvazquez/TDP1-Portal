//
// Created by cecix on 6/06/19.
//

#include <string>
#include <iostream>
#include "Portal.h"
#include "entities/Chell.h"
#include "entities/EnergyBall.h"
#include "entities/BlueShot.h"
#include "OrangeShot.h"

Portal::Portal(b2Body* body, Coordinate* target,
        Orientation orientation, Direction type):
    Entity(PORTAL_NAME, body) {
    this->target = target;
    this->body->SetUserData(this);
    this->orientation = orientation;
    this->portal_type_target = type;
}

Direction Portal::getPortalType() {
    return portal_type_target;
}

void Portal::addPortalType(Direction type) {
    this->portal_type_target = type;
}

void Portal::handleCollision(Entity* entity) {
    const std::string& type = entity->getType();
    if (type == CHELL_NAME) {
        Chell* chell = dynamic_cast<Chell*>(entity);
        if (target != nullptr) {
            chell->teleport(target, portal_type_target);
        }
    }
    if (type == ROCK_NAME) {
        Rock* rock = dynamic_cast<Rock*>(entity);
        if (target != nullptr)  {
            rock->teleport(target, portal_type_target);
        }
    }
    if (type == EB_NAME) {
        EnergyBall* eb = dynamic_cast<EnergyBall*>(entity);
        if (target != nullptr) {
            eb->teleport(target, portal_type_target);
        }
    }
    if (type == BLUE_SHOT_NAME) {
        dynamic_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
        dynamic_cast<OrangeShot*>(entity)->die();
    }
}

Coordinate* Portal::getTarget() {
    return target;
}

Orientation Portal::getOrientation() {
    return orientation;
}

void Portal::addTarget(Coordinate* target) {
    this->target = target;
}

Portal::~Portal() {
    //if (target != nullptr) delete target;
}
