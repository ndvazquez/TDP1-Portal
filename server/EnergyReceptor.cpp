//
// Created by cecix on 15/06/19.
//

#include "EnergyReceptor.h"

EnergyReceptor::EnergyReceptor(b2Body* body, std::string type):
        Entity(type, body) {
    body->SetUserData(this);
    this->state = OFF;
}

bool EnergyReceptor::isActive() {
    return this->state == ON;
}

void EnergyReceptor::handleCollision(Entity *entity) {
}

void EnergyReceptor::activate() {
    this->state = ON;
}

SwitchState EnergyReceptor::getState() {
    return state;
}
