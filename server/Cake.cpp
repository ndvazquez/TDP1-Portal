//
// Created by cecix on 10/06/19.
//

#include <string>
#include "Cake.h"
#include "Chell.h"
#include "BlueShot.h"
#include "OrangeShot.h"

#define cakeType "Cake"

Cake::Cake(b2Body* body):
        Entity(cakeType, body) {
    body->SetUserData(this);
}

void Cake::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        static_cast<Chell*>(entity)->win();
    }
    if (type == "BlueShot") {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == "OrangeShot") {
        static_cast<OrangeShot*>(entity)->die();
    }
}
