//
// Created by cecix on 10/06/19.
//

#include <iostream>
#include "EnergyTransmitterDown.h"

EnergyTransmitterDown::EnergyTransmitterDown(b2Body* body):
    EnergyTransmitter(body)  {
}

Coordinate* EnergyTransmitterDown::throwEnergyBall() {
    float offset = gameConfiguration.offsetEnergyTransmitter;
    float x_pos = getHorizontalPosition();
    float y_pos = getVerticalPosition() - offset;
    if (isTimeToThrow()) {
        return new Coordinate(x_pos, y_pos);
    }
}
