//
// Created by cecix on 1/06/19.
//

#ifndef PORTAL_ORANGEPORTAL_H
#define PORTAL_ORANGEPORTAL_H

#include "Portal.h"
#include "Coordinate.h"

class OrangePortal: public Portal {
public:
    explicit OrangePortal(b2Body* body);
};

#endif //PORTAL_ORANGEPORTAL_H
