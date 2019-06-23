//
// Created by cecix on 10/06/19.
//

#ifndef PORTAL_ENERGYTRANSMITTERRIGHT_H
#define PORTAL_ENERGYTRANSMITTERRIGHT_H

#include "entities/EnergyTransmitter.h"

class EnergyTransmitterRight: public EnergyTransmitter {
public:
    explicit EnergyTransmitterRight(b2Body* body);

    /* Returns a Coordinate* that indicates the position
    * an EnergyBall should be thrown */
    Coordinate* throwEnergyBall() override;
};

#endif //PORTAL_ENERGYTRANSMITTERRIGHT_H
