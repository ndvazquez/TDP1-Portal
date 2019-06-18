//
// Created by cecix on 15/06/19.
//

#ifndef PORTAL_ENERGYRECEPTOR_H
#define PORTAL_ENERGYRECEPTOR_H


#include "Entity.h"
#include "../common/constants.h"
#include "ItemActivable.h"
#include "BlueShot.h"
#include "OrangeShot.h"

class EnergyReceptor: public ItemActivable {
public:
    EnergyReceptor(b2Body* body, std::string type);
    virtual void handleCollision(Entity* entity) override;
};

#endif //PORTAL_ENERGYRECEPTOR_H
