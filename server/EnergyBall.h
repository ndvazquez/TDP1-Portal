//
// Created by cecix on 19/05/19.
//

#ifndef PORTAL_ENERGYBALL_H
#define PORTAL_ENERGYBALL_H


#include "Dynamic.h"

class EnergyBall {
private:
    Dynamic dynamic;
public:
    EnergyBall(b2Body* body);
    void fly();
};


#endif //PORTAL_ENERGYBALL_H
