//
// Created by cecix on 25/05/19.
//

#include <string>
#include <iostream>
#include "Floor.h"
#include "Chell.h"
#include "OrangeShot.h"
#include "BlueShot.h"

Floor::Floor(b2Body* body):
        Entity(FLOOR_NAME, body) {
    body->SetUserData(this);
}

void Floor::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == CHELL_NAME) {
        static_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == BLUE_SHOT_NAME) {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
        static_cast<OrangeShot*>(entity)->die();
    }
}
