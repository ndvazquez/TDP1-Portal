//
// Created by cecix on 10/06/19.
//

#include "EnergyTransmitterLeft.h"

EnergyTransmitterLeft::EnergyTransmitterLeft(b2Body* body):
        EnergyTransmitter(body)  {
    this->type_transmitter = LEFT;
}

Coordinate* EnergyTransmitterLeft::throwEnergyBall() {
    float offset = gameConfiguration.offsetEnergyTransmitter;
    float x_pos = getHorizontalPosition() - offset;
    float y_pos = getVerticalPosition();
    if (isTimeToThrow()) {
        return new Coordinate(x_pos, y_pos);
    }
}
