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
    std::string type = entity->getType();
    if (type == CHELL_NAME) {
        static_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == EB_NAME) {
        EnergyBall* energyBall = static_cast<EnergyBall*>(entity);
        float x_pos = getHorizontalPosition();
        float x_eb = energyBall->getHorizontalPosition();
        if (x_eb > x_pos) {
            activate();
            energyBall->die();
        }
    }
}
