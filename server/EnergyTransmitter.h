//
// Created by cecix on 17/05/19.
//

#ifndef PORTAL_ENERGYTRANSMITTER_H
#define PORTAL_ENERGYTRANSMITTER_H

#include <chrono>
#include "EnergyBall.h"

class EnergyTransmitter {
private:
    b2Body* body;
    std::chrono::system_clock::time_point timeStamp;

public:
    explicit EnergyTransmitter(b2Body* body);
    float getHorizontalPosition();
    float getVerticalPosition();
    bool throwEnergyBall();
};

#endif //PORTAL_ENERGYTRANSMITTER_H
