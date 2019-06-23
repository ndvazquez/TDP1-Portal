//
// Created by cecix on 19/06/19.
//

#include "PortalHolder.h"

PortalHolder::PortalHolder(Coordinate* portal, bool is_vertical, Direction type) {
    this->portal = portal;
    this->is_vertical = is_vertical;
    this->type = type;
}

bool PortalHolder::isVertical() {
    return is_vertical;
}

Coordinate* PortalHolder::getPortal() {
    return portal;
}

Direction PortalHolder::getPortalType() {
    return type;
}

PortalHolder::~PortalHolder() {
    delete portal;
}
