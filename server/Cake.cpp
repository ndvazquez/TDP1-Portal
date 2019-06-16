//
// Created by cecix on 10/06/19.
//

#include <string>
#include "Cake.h"
#include "Chell.h"
#include "BlueShot.h"
#include "OrangeShot.h"

Cake::Cake(b2Body* body):
        Entity(CAKE_NAME, body) {
    body->SetUserData(this);
}

void Cake::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == CHELL_NAME) {
        static_cast<Chell*>(entity)->win();
    }
    if (type == BLUE_SHOT_NAME) {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
        static_cast<OrangeShot*>(entity)->die();
    }
}
