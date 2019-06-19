//
// Created by cecix on 15/06/19.
//

#include "EnergyReceptorDown.h"
#include "Chell.h"
#include "EnergyBall.h"

EnergyReceptorDown::EnergyReceptorDown(b2Body* body):
    EnergyReceptor(body, ER_DOWN_NAME) {
}

void EnergyReceptorDown::handleCollision(Entity* entity) {
    const std::string& type = entity->getType();
    if (type == CHELL_NAME) {
        dynamic_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == EB_NAME) {
        EnergyBall* energyBall = dynamic_cast<EnergyBall*>(entity);
        float y_pos = getVerticalPosition();
        float y_eb = energyBall->getVerticalPosition();
        if (y_eb < y_pos) {
            activate();
            energyBall->die();
        }
    }
    if (type == BLUE_SHOT_NAME) {
        dynamic_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
        dynamic_cast<OrangeShot*>(entity)->die();
    }
}
