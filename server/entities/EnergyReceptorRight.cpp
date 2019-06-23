//
// Created by cecix on 15/06/19.
//

#include "EnergyReceptorRight.h"
#include "Chell.h"
#include "EnergyBall.h"

EnergyReceptorRight::EnergyReceptorRight(b2Body* body):
        EnergyReceptor(body, ER_RIGHT_NAME) {
}

void EnergyReceptorRight::handleCollision(Entity* entity) {
    const std::string& type = entity->getType();
    if (type == CHELL_NAME) {
        dynamic_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == EB_NAME) {
        EnergyBall *energyBall = dynamic_cast<EnergyBall *>(entity);
        float x_pos = getHorizontalPosition();
        float x_eb = energyBall->getHorizontalPosition();
        if (x_eb > x_pos) {
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
