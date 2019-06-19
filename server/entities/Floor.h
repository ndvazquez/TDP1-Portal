//
// Created by cecix on 25/05/19.
//

#ifndef PORTAL_FLOOR_H
#define PORTAL_FLOOR_H


#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"

class Floor: public Entity {
public:
    explicit Floor(b2Body* body);
    virtual void handleCollision(Entity* entity) override;
};


#endif //PORTAL_FLOOR_H
