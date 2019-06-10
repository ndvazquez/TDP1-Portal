//
// Created by cecix on 10/06/19.
//

#ifndef PORTAL_ENERGYTRANSMITTERDOWN_H
#define PORTAL_ENERGYTRANSMITTERDOWN_H

#include "EnergyTransmitter.h"

class EnergyTransmitterDown: public EnergyTransmitter {
public:
    explicit EnergyTransmitterDown(b2Body* body);
    virtual Coordinate* throwEnergyBall() override;
};


#endif //PORTAL_ENERGYTRANSMITTERDOWN_H
