//
// Created by cecix on 15/06/19.
//

#include "EnergyReceptorRight.h"
#include "Chell.h"
#include "EnergyBall.h"

#define eRRightType "EnergyReceptorRight"

EnergyReceptorRight::EnergyReceptorRight(b2Body* body):
        EnergyReceptor(body, eRRightType) {
}

void EnergyReceptorRight::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        static_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == "EnergyBall") {
        EnergyBall* energyBall = static_cast<EnergyBall*>(entity);
        float x_pos = getHorizontalPosition();
        float x_eb = energyBall->getHorizontalPosition();
        if (x_eb > x_pos) {
            activate();
            energyBall->die();
        }
    }
}
