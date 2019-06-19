//
// Created by cecix on 10/06/19.
//

#ifndef PORTAL_ENERGYTRANSMITTERUP_H
#define PORTAL_ENERGYTRANSMITTERUP_H


#include "entities/EnergyTransmitter.h"

class EnergyTransmitterUp: public EnergyTransmitter {
public:
    explicit EnergyTransmitterUp(b2Body* body);
    virtual Coordinate* throwEnergyBall() override;
};

#endif //PORTAL_ENERGYTRANSMITTERUP_H
