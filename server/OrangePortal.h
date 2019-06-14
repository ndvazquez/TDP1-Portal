//
// Created by cecix on 11/06/19.
//

#ifndef PORTAL_ORANGEPORTAL_H
#define PORTAL_ORANGEPORTAL_H


#include "Coordinate.h"
#include "../common/constants.h"

class OrangePortal {
private:
    Coordinate* portal;
    bool is_vertical;
    PortalType type;
public:
    OrangePortal(Coordinate* portal, bool is_vertical, PortalType type);
    Coordinate* getPortal();
    PortalType getType();
    bool isVertical();
};


#endif //PORTAL_ORANGEPORTAL_H
