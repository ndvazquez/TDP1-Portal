//
// Created by cecix on 11/06/19.
//

#ifndef PORTAL_BLUEPORTAL_H
#define PORTAL_BLUEPORTAL_H

#include "Coordinate.h"

class BluePortal {
private:
    Coordinate* portal;
    bool is_vertical;
public:
    BluePortal(Coordinate* portal, bool is_vertical);
    Coordinate* getPortal();
    bool isVertical();
};

#endif //PORTAL_BLUEPORTAL_H
