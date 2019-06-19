//
// Created by cecix on 10/06/19.
//

#ifndef PORTAL_ENERGYTRANSMITTERLEFT_H
#define PORTAL_ENERGYTRANSMITTERLEFT_H


#include "EnergyTransmitter.h"

class EnergyTransmitterLeft: public EnergyTransmitter {
public:
    explicit EnergyTransmitterLeft(b2Body* body);
    virtual Coordinate* throwEnergyBall() override;
};


#endif //PORTAL_ENERGYTRANSMITTERLEFT_H
