//
// Created by cecix on 16/06/19.
//

#include "PortalManager.h"

PortalManager::PortalManager(std::unordered_map<std::string, Portal *> &portals, PhysicsWorld *world):
    portals(portals), world(world) {
}

void PortalManager::addPortal(std::string id, float v_side, float h_side,
                          Coordinate* origin, Coordinate* target,
                          PortalOrientation orientation, Direction type) {
    float x_pos = origin->getX();
    float y_pos = origin->getY();

    b2Body* portal_body = world->addStaticRectangle(v_side, h_side, x_pos, y_pos);
    Portal* portal = new Portal(portal_body, target, orientation, type);
    portals.insert({id, portal});
}

void PortalManager::managePortals(Chell *chell, std::string id) {
    PortalHolder *blue_portal = chell->getBluePortal();
    PortalHolder *orange_portal = chell->getOrangePortal();
    std::string id_orange = id;
    std::string replaced = "Chell";
    id_orange.replace(0, replaced.length(), "OrangePortal");
    std::string id_blue = id;
    id_blue.replace(0, replaced.length(), "BluePortal");

    auto it = portals.find(id_blue);
    if (it != portals.end()) {
        Portal *portal = it->second;
        float x_portal = portal->getHorizontalPosition();
        float y_portal = portal->getVerticalPosition();
        Coordinate coord_portal(x_portal, y_portal);
        if ((blue_portal != nullptr && *blue_portal->getPortal() != coord_portal)
            || blue_portal == nullptr) {
            world->destroyBody(portal->getBody());

            delete it->second;
            portals.erase(it);
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
            addPortal(id_blue, PORTAL_HEIGHT, PORTAL_WIDTH, blue_portal->getPortal(),
                      orange_portal_coord, VERTICAL, INVALID);
        } else {
            addPortal(id_blue, PORTAL_WIDTH, PORTAL_HEIGHT, blue_portal->getPortal(),
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
            world->destroyBody(it->second->getBody());
            delete it->second;
            portals.erase(it);
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
            addPortal(id_orange, PORTAL_HEIGHT, PORTAL_WIDTH, orange_portal->getPortal(),
                      blue_portal_coord, VERTICAL, INVALID);
        } else {
            addPortal(id_orange, PORTAL_WIDTH, PORTAL_HEIGHT, orange_portal->getPortal(),
                      blue_portal_coord, HORIZONTAL, INVALID);
        }
    }
}