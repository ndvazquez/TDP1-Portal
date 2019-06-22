//
// Created by ndv on 6/22/19.
//

#ifndef PORTAL_ENERGYBARVIEW_H
#define PORTAL_ENERGYBARVIEW_H

#include <yaml-cpp/yaml.h>
#include "View.h"
#include "../../common/Sprite.h"
#include "../../common/constants.h"

#define TEXTURES_ENERGY_BAR_KEY "EnergyBar"

class EnergyBarView : public View {
    Sprite* sprite;
public:
    EnergyBarView(Window &window,
            int xPos,
            int yPos,
            int factor,
            YAML::Node texturesData);
    ~EnergyBarView()();
    void playAnimation(const SDL_Rect& camera);
    void setState(int state);
};


#endif //PORTAL_ENERGYBARVIEW_H
