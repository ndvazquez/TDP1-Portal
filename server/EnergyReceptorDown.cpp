//
// Created by cecix on 15/06/19.
//

#include "EnergyReceptorDown.h"
#include "Chell.h"
#include "EnergyBall.h"

#define eRDownType "EnergyReceptorDown"

EnergyReceptorDown::EnergyReceptorDown(b2Body* body):
    EnergyReceptor(body, eRDownType) {
}

void EnergyReceptorDown::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == "Chell") {
        static_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == "EnergyBall") {
        EnergyBall* energyBall = static_cast<EnergyBall*>(entity);
        float y_pos = getVerticalPosition();
        float y_eb = energyBall->getVerticalPosition();
        if (y_eb < y_pos) activate();
    }
}
