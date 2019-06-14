//
// Created by cecix on 11/06/19.
//

#include "BluePortal.h"

BluePortal::BluePortal(Coordinate *portal, bool is_vertical) {
    this->portal = portal;
    this->is_vertical = is_vertical;
}

bool BluePortal::isVertical() {
    return is_vertical;
}

Coordinate* BluePortal::getPortal() {
    return portal;
}
