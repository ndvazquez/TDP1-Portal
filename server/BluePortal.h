//
// Created by cecix on 11/06/19.
//

#ifndef PORTAL_BLUEPORTAL_H
#define PORTAL_BLUEPORTAL_H

#include "Coordinate.h"
#include "../common/constants.h"

class BluePortal {
private:
    Coordinate* portal;
    bool is_vertical;
    PortalType type;
public:
    BluePortal(Coordinate* portal, bool is_vertical, PortalType type);
    Coordinate* getPortal();
    bool isVertical();
    PortalType getPortalType();
    ~BluePortal();
};

#endif //PORTAL_BLUEPORTAL_H
