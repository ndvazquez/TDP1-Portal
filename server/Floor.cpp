//
// Created by cecix on 25/05/19.
//

#include <string>
#include "Floor.h"
#include "Chell.h"

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
    if (type == "Rock") {
        static_cast<Rock*>(entity)->onFloor(true);
    }
}
