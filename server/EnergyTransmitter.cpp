//
// Created by cecix on 17/05/19.
//

#include <Box2D/Dynamics/b2Body.h>
#include "EnergyTransmitter.h"

EnergyTransmitter::EnergyTransmitter(b2Body* body):
    body(body) {
    this->timeStamp = std::chrono::system_clock::now();
}

float EnergyTransmitter::getHorizontalPosition() {
    return this->body->GetPosition().x;
}

float EnergyTransmitter::getVerticalPosition() {
    return this->body->GetPosition().y;
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