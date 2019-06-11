//
// Created by cecix on 17/05/19.
//

#ifndef PORTAL_BUTTON_H
#define PORTAL_BUTTON_H

#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"
#include "../common/constants.h"

class Button: public Entity {
private:
    b2Body* body;
    ButtonState state;

public:
    explicit Button(b2Body* body);
    virtual void handleCollision(Entity* entity) override;
    void activate();
    bool isActive();
    ButtonState getState();
};


#endif //PORTAL_BUTTON_H
