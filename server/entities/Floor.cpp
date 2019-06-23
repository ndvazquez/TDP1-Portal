//
// Created by cecix on 25/05/19.
//

#include <string>
#include <iostream>
#include "Floor.h"
#include "entities/Chell.h"
#include "OrangeShot.h"
#include "entities/BlueShot.h"

Floor::Floor(b2Body* body):
        Entity(FLOOR_NAME, body) {
    body->SetUserData(this);
}

void Floor::handleCollision(Entity* entity) {
    const std::string& type = entity->getType();
    if (type == CHELL_NAME) {
        dynamic_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == BLUE_SHOT_NAME) {
        dynamic_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
        dynamic_cast<OrangeShot*>(entity)->die();
    }
}
