//
// Created by cecix on 19/05/19.
//

#ifndef PORTAL_ENERGYBALLVERTICAL_H
#define PORTAL_ENERGYBALLVERTICAL_H


#include "EnergyBall.h"

class EnergyBallVertical: public EnergyBall {
public:
    explicit EnergyBallVertical(b2Body* body);
    virtual void fly() override;
};

#endif //PORTAL_ENERGYBALLVERTICAL_H
