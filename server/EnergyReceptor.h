//
// Created by cecix on 15/06/19.
//

#ifndef PORTAL_ENERGYRECEPTOR_H
#define PORTAL_ENERGYRECEPTOR_H


#include "Entity.h"
#include "../common/constants.h"

class EnergyReceptor: public Entity {
private:
    SwitchState state;

public:
    EnergyReceptor(b2Body* body, std::string type);
    virtual void handleCollision(Entity* entity) override;
    bool isActive();
    void activate();
    SwitchState getState();
};

#endif //PORTAL_ENERGYRECEPTOR_H
