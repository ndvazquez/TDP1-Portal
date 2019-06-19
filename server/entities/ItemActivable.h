//
// Created by cecix on 15/06/19.
//

#ifndef PORTAL_ITEMACTIVABLE_H
#define PORTAL_ITEMACTIVABLE_H


#include "Entity.h"
#include "../../common/constants.h"

class ItemActivable: public Entity {
    SwitchState state;

public:
    ItemActivable(std::string type, b2Body* body);
    virtual void handleCollision(Entity* entity) override;
    bool isActive();
    void activate();
    void desactivate();
    SwitchState getState();
};


#endif //PORTAL_ITEMACTIVABLE_H
