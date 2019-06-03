//
// Created by cecix on 2/06/19.
//

#ifndef PORTAL_SHOT_H
#define PORTAL_SHOT_H


#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"

class Shot: public Entity {
public:
    explicit Shot(b2Body* body);
    virtual void handleCollision(Entity* entity) override;
};


#endif //PORTAL_SHOT_H
