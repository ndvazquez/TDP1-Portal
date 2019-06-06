//
// Created by cecix on 13/05/19.
//

#ifndef PORTAL_BRICKBLOCK_H
#define PORTAL_BRICKBLOCK_H

#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"

class BrickBlock: public Entity {
public:
    explicit BrickBlock(b2Body* body);
    virtual void handleCollision(Entity* entity) override;
};

#endif //PORTAL_BRICKBLOCK_H
