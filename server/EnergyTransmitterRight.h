//
// Created by cecix on 10/06/19.
//

#ifndef PORTAL_ENERGYTRANSMITTERRIGHT_H
#define PORTAL_ENERGYTRANSMITTERRIGHT_H


#include "EnergyTransmitter.h"

class EnergyTransmitterRight: public EnergyTransmitter {
public:
    explicit EnergyTransmitterRight(b2Body* body);
    virtual Coordinate* throwEnergyBall() override;
};

#endif //PORTAL_ENERGYTRANSMITTERRIGHT_H
