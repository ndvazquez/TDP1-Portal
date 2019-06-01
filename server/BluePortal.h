//
// Created by cecix on 1/06/19.
//

#ifndef PORTAL_BLUEPORTAL_H
#define PORTAL_BLUEPORTAL_H

#include "Portal.h"
#include "Coordinate.h"

class BluePortal: public Portal {
public:
    explicit BluePortal(b2Body* body);
};

#endif //PORTAL_BLUEPORTAL_H
