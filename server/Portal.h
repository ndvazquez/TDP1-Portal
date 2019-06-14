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
    PortalType type;

public:
    Portal(b2Body* body, Coordinate* target, PortalOrientation orientation, PortalType type);
    Coordinate* getTarget();
    virtual void handleCollision(Entity* entity) override;
    PortalOrientation getOrientation();
    PortalType getPortalType();
    void addTarget(Coordinate* target);
    ~Portal();
};


#endif //PORTAL_PORTAL_H
