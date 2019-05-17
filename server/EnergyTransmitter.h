//
// Created by cecix on 17/05/19.
//

#ifndef PORTAL_ENERGYTRANSMITTER_H
#define PORTAL_ENERGYTRANSMITTER_H

class EnergyTransmitter {
private:
    b2Body* body;

public:
    EnergyTransmitter(b2Body* body);
    float getHorizontalPosition();
    float getVerticalPosition();
};

#endif //PORTAL_ENERGYTRANSMITTER_H
