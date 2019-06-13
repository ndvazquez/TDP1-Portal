//
// Created by cecix on 18/05/19.
//

#include <string>

#include "Acid.h"
#include "Chell.h"
#include "BlueShot.h"
#include "OrangeShot.h"

#define acidType "Acid"

Acid::Acid(b2Body* body):
    Entity(acidType, body) {
    body->SetUserData(this);
}

void Acid::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        static_cast<Chell*>(entity)->die();
    }
    if (type == "BlueShot") {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == "OrangeShot") {
        static_cast<OrangeShot*>(entity)->die();
    }
}
