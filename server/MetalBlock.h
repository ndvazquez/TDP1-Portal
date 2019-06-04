//
// Created by cecix on 13/05/19.
//

#ifndef PORTAL_METALBLOCK_H
#define PORTAL_METALBLOCK_H

#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"
#include "Coordinate.h"

class MetalBlock: public Entity {
private:
    bool portal;

public:
    explicit MetalBlock(b2Body* body);
    virtual void handleCollision(Entity* entity) override;
    void createPortal();
    bool hasPortal();
};

#endif //PORTAL_METALBLOCK_H
