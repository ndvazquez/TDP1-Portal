//
// Created by cecix on 6/06/19.
//

#include "Portal.h"

Portal::Portal() {
    this->orange_portal = nullptr;
    this->blue_portal = nullptr;
}

void Portal::addOrangePortal(Coordinate* portal) {
    if (orange_portal != nullptr) delete orange_portal;
    this->orange_portal = portal;
}

void Portal::addBluePortal(Coordinate* portal) {
    if (blue_portal != nullptr) delete blue_portal;
    this->blue_portal = portal;
}

Coordinate* Portal::teleport(Coordinate* origin) {
    if (orange_portal == nullptr || blue_portal == nullptr) return nullptr;

    float x_orange = orange_portal->getX();
    float y_orange = orange_portal->getY();
    float x_blue = blue_portal->getX();
    float y_blue = blue_portal->getY();
    float x_coordinate = origin->getX();
    float y_coordinate = origin->getY();

    if (x_coordinate == x_orange && y_coordinate == y_orange) {
        return blue_portal;
    } else if (x_coordinate == x_blue && y_coordinate == y_blue) {
        return orange_portal;
    }
}

Coordinate* Portal::getBluePortal() {
    return blue_portal;
}

Coordinate* Portal::getOrangePortal() {
    return orange_portal;
}

Portal::~Portal() {
    if (orange_portal != nullptr) delete orange_portal;
    if (blue_portal != nullptr) delete blue_portal;
}
