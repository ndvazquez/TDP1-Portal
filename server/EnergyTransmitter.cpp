//
// Created by cecix on 17/05/19.
//

#include <Box2D/Dynamics/b2Body.h>
#include <iostream>
#include "EnergyTransmitter.h"
#include "BlueShot.h"
#include "OrangeShot.h"

#define energyTransmitterType "EnergyTransmitter"

EnergyTransmitter::EnergyTransmitter(b2Body* body):
    Entity(energyTransmitterType, body) {
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
    std::string type = entity->getType();
    if (type == "BlueShot") {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == "OrangeShot") {
        static_cast<OrangeShot*>(entity)->die();
    }
    if (type == "Chell") {
        static_cast<Chell*>(entity)->onFloor(true);
    }
}
