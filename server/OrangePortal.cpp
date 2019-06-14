//
// Created by cecix on 11/06/19.
//

#include "OrangePortal.h"

OrangePortal::OrangePortal(Coordinate *portal, bool is_vertical, PortalType type) {
    this->portal = portal;
    this->is_vertical = is_vertical;
    this->type = type;
}

bool OrangePortal::isVertical() {
    return is_vertical;
}

Coordinate* OrangePortal::getPortal() {
    return portal;
}

PortalType OrangePortal::getPortalType() {
    return type;
}
