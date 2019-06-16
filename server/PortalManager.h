//
// Created by cecix on 16/06/19.
//

#ifndef PORTAL_PORTALMANAGER_H
#define PORTAL_PORTALMANAGER_H

#include <unordered_map>
#include "Portal.h"
#include "PhysicsWorld.h"
#include "Chell.h"

class PortalManager {
private:
    std::unordered_map<std::string, Portal*> &portals;
    PhysicsWorld* world;

public:
    PortalManager(std::unordered_map<std::string, Portal*>& portals,
    PhysicsWorld* world);
    void addPortal(std::string id, float v_side, float h_side,
            Coordinate* origin, Coordinate* target,
            PortalOrientation orientation, PortalType type);
    void managePortals(Chell* chell, std::string id);
};

#endif //PORTAL_PORTALMANAGER_H
