//
// Created by cecix on 13/05/19.
//

#ifndef PORTAL_ROCKBLOCK_H
#define PORTAL_ROCKBLOCK_H

#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"

class RockBlock: public Entity {
public:
    explicit RockBlock(b2Body* body);
    virtual void handleCollision(Entity* entity) override;
};

#endif //PORTAL_ROCKBLOCK_H
