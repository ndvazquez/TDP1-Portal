//
// Created by cecix on 25/05/19.
//

#include <string>
#include <iostream>
#include "Floor.h"
#include "Chell.h"
#include "OrangeShot.h"
#include "BlueShot.h"

#define floorType "Floor"

Floor::Floor(b2Body* body):
        Entity(floorType, body) {
    body->SetUserData(this);
}

void Floor::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        static_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == "BlueShot") {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == "OrangeShot") {
        static_cast<OrangeShot*>(entity)->die();
    }
}
