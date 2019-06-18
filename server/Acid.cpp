//
// Created by cecix on 18/05/19.
//

#include <string>

#include "Acid.h"
#include "Chell.h"
#include "BlueShot.h"
#include "OrangeShot.h"

Acid::Acid(b2Body* body):
    Entity(ACID_NAME, body) {
    body->SetUserData(this);
}

void Acid::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == CHELL_NAME) {
        static_cast<Chell*>(entity)->die();
    }
    if (type == BLUE_SHOT_NAME) {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
        static_cast<OrangeShot*>(entity)->die();
    }
}
