//
// Created by cecix on 6/06/19.
//

#ifndef PORTAL_PORTAL_H
#define PORTAL_PORTAL_H


#include "Coordinate.h"
#include "Entity.h"
#include "../common/constants.h"

class Portal: public Entity {
private:
    Coordinate* target;
    PortalOrientation orientation;

public:
    Portal(b2Body* body, Coordinate* target, PortalOrientation orientation);
    Coordinate* getTarget();
    virtual void handleCollision(Entity* entity) override;
    PortalOrientation getOrientation();
    void addTarget(Coordinate* target);
    ~Portal();
};


#endif //PORTAL_PORTAL_H
