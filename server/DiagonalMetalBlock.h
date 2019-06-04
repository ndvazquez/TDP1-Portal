//
// Created by cecix on 13/05/19.
//

#ifndef PORTAL_DIAGONALMETALBLOCK_H
#define PORTAL_DIAGONALMETALBLOCK_H

#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"

class DiagonalMetalBlock: public Entity  {
private:
    bool portal;
public:
    explicit DiagonalMetalBlock(b2Body* body);
    virtual void handleCollision(Entity* entity) override;
    void createPortal();
    bool hasPortal();
};


#endif //PORTAL_DIAGONALMETALBLOCK_H
