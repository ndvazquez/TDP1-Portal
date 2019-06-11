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
    bool vertical_portal;
    bool horizontal_portal;
    MetalBlock* other;

public:
    explicit MetalBlock(b2Body* body);
    virtual void handleCollision(Entity* entity) override;
    void createVerticalPortal();
    void createHorizontalPortal();
    bool hasVerticalPortal();
    bool hasHorizontalPortal();
    void deletePortal();
    void addOtherPortal(MetalBlock* other);
    Coordinate* getOtherPortal();
};

#endif //PORTAL_METALBLOCK_H
