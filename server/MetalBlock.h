//
// Created by cecix on 13/05/19.
//

#ifndef PORTAL_METALBLOCK_H
#define PORTAL_METALBLOCK_H

#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"

class MetalBlock: public Entity {
private:
    b2Body* body;

public:
    explicit MetalBlock(b2Body* body);
    float getHorizontalPosition();
    float getVerticalPosition();
    virtual void handleCollision(Entity* entity) override;
};

#endif //PORTAL_METALBLOCK_H
