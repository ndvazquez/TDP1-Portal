//
// Created by cecix on 15/06/19.
//

#include "EnergyReceptorUp.h"
#include "Chell.h"
#include "EnergyBall.h"

EnergyReceptorUp::EnergyReceptorUp(b2Body* body):
        EnergyReceptor(body, ER_UP_NAME) {
}

void EnergyReceptorUp::handleCollision(Entity* entity) {
    const std::string& type = entity->getType();
    if (type == CHELL_NAME) {
        dynamic_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == EB_NAME) {
        EnergyBall* energyBall = dynamic_cast<EnergyBall*>(entity);
        float y_pos = getVerticalPosition();
        float y_eb = energyBall->getVerticalPosition();
        if (y_eb > y_pos) {
            activate();
            energyBall->die();
        } else {
            energyBall->invertDirection();
        }
    }
    if (type == BLUE_SHOT_NAME) {
        dynamic_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
        dynamic_cast<OrangeShot*>(entity)->die();
    }
}
