//
// Created by cecix on 15/06/19.
//

#include "PortalsManager.h"
/*
PortalsManager::PortalsManager(std::unordered_map<std::string, Portal *> &portals,
        Stage* stage, b2World* world):
        portals(portals), stage(stage), world(world) {
}

void PortalsManager::managePortals(Chell* chell, std::string id) {
    BluePortal *blue_portal = chell->getBluePortal();
    OrangePortal *orange_portal = chell->getOrangePortal();
    std::string id_orange = id;
    std::string replaced = "Chell";
    id_orange.replace(0, replaced.length(), "OrangePortal");
    std::string id_blue = id;
    id_blue.replace(0, replaced.length(), "BluePortal");

    std::unordered_map<std::string, Portal*>::iterator it;

    it = portals.find(id_blue);
    if (it != portals.end()) {
        Portal *portal = it->second;
        float x_portal = portal->getHorizontalPosition();
        float y_portal = portal->getVerticalPosition();
        Coordinate coord_portal(x_portal, y_portal);
        if ((blue_portal != nullptr && *blue_portal->getPortal() != coord_portal)
            || blue_portal == nullptr) {
            world->DestroyBody(portal->getBody());
            portals.erase(it->first);
        }
        if (orange_portal != nullptr) {
            Coordinate* orange_portal_coord = chell->getOrangePortalToTeleport();
            portal->addTarget(orange_portal_coord);
            portal->addPortalType(orange_portal->getPortalType());
        }
    }
    else if (blue_portal != nullptr) {
        Coordinate* orange_portal_coord = chell->getOrangePortalToTeleport();
        if (blue_portal->isVertical()) {
            stage->addPortal(id_blue, PORTAL_HEIGHT, PORTAL_WIDTH, blue_portal->getPortal(),
                      orange_portal_coord, VERTICAL, INVALID);
        } else {
            stage->addPortal(id_blue, PORTAL_WIDTH, PORTAL_HEIGHT, blue_portal->getPortal(),
                      orange_portal_coord, HORIZONTAL, INVALID);
        }
    }

    it = portals.find(id_orange);
    if (it != portals.end()) {
        Portal* portal = it->second;
        float x_portal = portal->getHorizontalPosition();
        float y_portal = portal->getVerticalPosition();
        Coordinate coord_portal(x_portal, y_portal);
        if ((orange_portal != nullptr && *orange_portal->getPortal() != coord_portal)
            || orange_portal == nullptr) {
            world->DestroyBody(it->second->getBody());
            portals.erase(it->first);
        }
        if (blue_portal != nullptr) {
            Coordinate* blue_portal_coord = chell->getBluePortalToTeleport();
            portal->addTarget(blue_portal_coord);
            portal->addPortalType(blue_portal->getPortalType());
        }
    }
    else if (orange_portal != nullptr) {
        Coordinate* blue_portal_coord = chell->getBluePortalToTeleport();
        if (orange_portal->isVertical()) {
            stage->addPortal(id_orange, PORTAL_HEIGHT, PORTAL_WIDTH, orange_portal->getPortal(),
                      blue_portal_coord, VERTICAL, INVALID);
        } else {
            stage->addPortal(id_orange, PORTAL_WIDTH, PORTAL_HEIGHT, orange_portal->getPortal(),
                      blue_portal_coord, HORIZONTAL, INVALID);
        }
    }
}
*/