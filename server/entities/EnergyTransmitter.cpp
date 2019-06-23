//
// Created by cecix on 17/05/19.
//

#include <Box2D/Dynamics/b2Body.h>
#include <iostream>
#include "EnergyTransmitter.h"
#include "BlueShot.h"
#include "OrangeShot.h"

EnergyTransmitter::EnergyTransmitter(b2Body* body):
    Entity(ET_NAME, body) {
    this->timeStamp = std::chrono::system_clock::now();
    body->SetUserData(this);
}

bool EnergyTransmitter::isTimeToThrow() {
    auto end = std::chrono::system_clock::now();
    auto difference = std::chrono::duration_cast<std::chrono::milliseconds>
            (end - timeStamp).count();
    float deathTime = gameConfiguration.deathTimeEnergyBall;
    float delay = gameConfiguration.delayEnergyTransmitter;
    if (difference <= deathTime + delay) return false; //throws energy_ball
    timeStamp = std::chrono::system_clock::now();
    return true;
}

void EnergyTransmitter::handleCollision(Entity *entity) {
    const std::string& type = entity->getType();
    if (type == BLUE_SHOT_NAME) {
        dynamic_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
        dynamic_cast<OrangeShot*>(entity)->die();
    }
    if (type == CHELL_NAME) {
        dynamic_cast<Chell*>(entity)->onFloor(true);
    }
    if (type == EB_NAME) {
        dynamic_cast<EnergyBall*>(entity)->invertDirection();
    }
}

Direction EnergyTransmitter::getTypeTransmitter() {
    return type_transmitter;
}
