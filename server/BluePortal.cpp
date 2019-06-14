//
// Created by cecix on 11/06/19.
//

#include "BluePortal.h"

BluePortal::BluePortal(Coordinate *portal, bool is_vertical, PortalType type) {
    this->portal = portal;
    this->is_vertical = is_vertical;
    this->type = type;
}

bool BluePortal::isVertical() {
    return is_vertical;
}

Coordinate* BluePortal::getPortal() {
    return portal;
}

PortalType BluePortal::getPortalType() {
    return type;
}
