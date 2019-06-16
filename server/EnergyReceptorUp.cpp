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
    std::string type = entity->getType();
    if (type == CHELL_NAME) {
        static_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == EB_NAME) {
        EnergyBall* energyBall = static_cast<EnergyBall*>(entity);
        float y_pos = getVerticalPosition();
        float y_eb = energyBall->getVerticalPosition();
        if (y_eb > y_pos) {
            activate();
            energyBall->die();
        }
    }
}
