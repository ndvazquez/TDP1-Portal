//
// Created by cecix on 6/06/19.
//

#ifndef PORTAL_PORTAL_H
#define PORTAL_PORTAL_H


#include "Coordinate.h"

class Portal {
private:
    Coordinate* orange_portal;
    Coordinate* blue_portal;

public:
    Portal();
    void addOrangePortal(Coordinate* portal);
    void addBluePortal(Coordinate* portal);
    Coordinate* teleport(Coordinate* origin);
    Coordinate* getOrangePortal();
    Coordinate* getBluePortal();
    ~Portal();
};


#endif //PORTAL_PORTAL_H
