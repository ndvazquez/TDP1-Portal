//
// Created by cecix on 6/06/19.
//

#ifndef PORTAL_PORTAL_H
#define PORTAL_PORTAL_H

#include "stage-support/Coordinate.h"
#include "Entity.h"
#include "../../common/constants.h"
#include "movements/Dynamic.h"

class Portal: public Entity {
private:
    Coordinate* target;
    PortalOrientation orientation;
    PortalType portal_type_target;

public:
    Portal(b2Body* body, Coordinate* target, PortalOrientation orientation, PortalType type);
    ~Portal();

    /* Returns the portal's target */
    Coordinate* getTarget();

    /* Handles collision against other objects in the world */
    void handleCollision(Entity* entity) override;

    /* Returns the portal's orientation */
    PortalOrientation getOrientation();

    /* Adds a target to the portal */
    void addTarget(Coordinate* target);

    /* Adds a type to the portal (right, left, up, down or invalid) */
    void addPortalType(PortalType type);

    /* Returns the portal's type */
    PortalType getPortalType();
};

#endif //PORTAL_PORTAL_H
