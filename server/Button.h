//
// Created by cecix on 17/05/19.
//

#ifndef PORTAL_BUTTON_H
#define PORTAL_BUTTON_H

#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"
#include "../common/constants.h"
#include "Dynamic.h"
#include "ItemActivable.h"

class Button: public ItemActivable {
    Dynamic dynamic;

public:
    explicit Button(b2Body* body);
    virtual void handleCollision(Entity* entity) override;
    void update();
};


#endif //PORTAL_BUTTON_H
