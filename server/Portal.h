//
// Created by cecix on 6/06/19.
//

#ifndef PORTAL_PORTAL_H
#define PORTAL_PORTAL_H


#include "Coordinate.h"
#include "Entity.h"

class Portal: public Entity {
private:
    Coordinate* orange_portal;
    Coordinate* blue_portal;

public:
    explicit Portal(b2Body* body);
    void addOrangePortal(Coordinate* portal);
    void addBluePortal(Coordinate* portal);
    Coordinate* teleport(Coordinate* origin);
    Coordinate* getOrangePortal();
    Coordinate* getBluePortal();
    virtual void handleCollision(Entity* entity) override;
    ~Portal();
};


#endif //PORTAL_PORTAL_H
