//
// Created by cecix on 1/06/19.
//

#ifndef PORTAL_PORTAL_H
#define PORTAL_PORTAL_H


#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"
#include "Coordinate.h"

class Portal: public Entity {
protected:
    b2Body* body;
    Coordinate* other_portal;

public:
    explicit Portal(b2Body* body);
    float getHorizontalPosition();
    float getVerticalPosition();
    virtual void handleCollision(Entity* entity) override;
    void addOtherPortal(Coordinate* coordinate);
    Coordinate* getOtherPortal();
};

#endif //PORTAL_PORTAL_H
