//
// Created by cecix on 16/06/19.
//

#ifndef PORTAL_PORTALMANAGER_H
#define PORTAL_PORTALMANAGER_H

#include <unordered_map>
#include "entities/Portal.h"
#include "stage-support/PhysicsWorld.h"
#include "entities/Chell.h"

class PortalManager {
private:
    std::unordered_map<std::string, Portal*> &portals;
    PhysicsWorld* world;

public:
    PortalManager(std::unordered_map<std::string, Portal*>& portals,
    PhysicsWorld* world);

    /* Adds a portal to the world */
    void addPortal(std::string id, float v_side, float h_side,
            Coordinate* origin, Coordinate* target,
            Orientation orientation, Direction type);

    /* Organizate portals in the world */
    void managePortals(Chell* chell, std::string id);
};

#endif //PORTAL_PORTALMANAGER_H
