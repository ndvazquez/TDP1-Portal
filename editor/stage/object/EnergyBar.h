//
// Created by camix on 19/06/19.
//

#ifndef PORTAL_ENERGYBAR_H
#define PORTAL_ENERGYBAR_H


#include "StaticObject.h"

class EnergyBar : public StaticObject {
public:
    EnergyBar(std::string &path, Window &window, int id, int w, int h);
    ~EnergyBar();

    bool hasGravity();

};


#endif //PORTAL_ENERGYBAR_H
