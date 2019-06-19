//
// Created by cecix on 19/06/19.
//

#ifndef PORTAL_PORTALHOLDER_H
#define PORTAL_PORTALHOLDER_H

#include <stage-support/Coordinate.h>
#include "../../common/constants.h"

class PortalHolder {
private:
    Coordinate* portal;
    bool is_vertical;
    PortalType type;

public:
    PortalHolder(Coordinate* portal, bool is_vertical, PortalType type);
    ~PortalHolder();

    /* Returns a Coordinate* that indicates the location of the portal */
    Coordinate* getPortal();

    /* Returns a boolean that indicates if the portal is vertical */
    bool isVertical();

    /* Returns the Portal's type */
    PortalType getPortalType();
};

#endif //PORTAL_BLUEPORTAL_H
