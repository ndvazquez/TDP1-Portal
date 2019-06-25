//
// Created by ndv on 5/21/19.
//

#ifndef PORTAL_ENERGYBALLVIEW_H
#define PORTAL_ENERGYBALLVIEW_H

#include "../../common/AnimatedSprite.h"
#include "../../common/Window.h"
#include <string>
#include <yaml-cpp/yaml.h>
#include "View.h"
#include "../../common/constants.h"

#define TEXTURES_EB_KEY "EnergyBall"

class EnergyBallView : public View {
    AnimatedSprite* animation;
public:
    EnergyBallView(Window &window,
            int xPos,
            int yPos,
            int factor,
            YAML::Node& texturesData);
    ~EnergyBallView();
    void playAnimation(const SDL_Rect& camera);
    void setState(int state);
};


#endif //PORTAL_ENERGYBALLVIEW_H
