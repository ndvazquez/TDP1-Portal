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
    std::string type = entity->getType();
    if (type == CHELL_NAME) {
        static_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == EB_NAME) {
        EnergyBall* energyBall = static_cast<EnergyBall*>(entity);
        float y_pos = getVerticalPosition();
        float y_eb = energyBall->getVerticalPosition();
        if (y_eb < y_pos) {
            activate();
            energyBall->die();
        }
    }
}
