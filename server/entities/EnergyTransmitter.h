//
// Created by cecix on 17/05/19.
//

#ifndef PORTAL_ENERGYTRANSMITTER_H
#define PORTAL_ENERGYTRANSMITTER_H

#include <chrono>
#include "EnergyBall.h"

class EnergyTransmitter: public Entity {
protected:
    std::chrono::system_clock::time_point timeStamp;

public:
    explicit EnergyTransmitter(b2Body* body);

    /* Returns boolean that indicates if it's time to throw an EnergyBall */
    bool isTimeToThrow();

    /* Throws an EnergyBall */
    virtual Coordinate* throwEnergyBall() = 0;

    /* Handles collision against other objects in the world */
    void handleCollision(Entity* entity) override;
};

#endif //PORTAL_ENERGYTRANSMITTER_H
