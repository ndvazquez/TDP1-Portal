//
// Created by cecix on 17/05/19.
//

#include <Box2D/Dynamics/b2Body.h>
#include "EnergyTransmitter.h"

EnergyTransmitter::EnergyTransmitter(b2Body* body):
        body(body) {
}

float EnergyTransmitter::getHorizontalPosition() {
    return this->body->GetPosition().x;
}

float EnergyTransmitter::getVerticalPosition() {
    return this->body->GetPosition().y;
}
