//
// Created by camix on 19/06/19.
//

#include "EnergyBar.h"

EnergyBar::EnergyBar(std::string &path, Window &window, int id, int w, int h) :
        StaticObject(path, window, id, w, h) {}

bool EnergyBar::hasGravity() {
    return false;
}


EnergyBar::~EnergyBar() = default;
