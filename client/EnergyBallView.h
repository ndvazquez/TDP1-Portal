//
// Created by ndv on 5/21/19.
//

#ifndef PORTAL_ENERGYBALLVIEW_H
#define PORTAL_ENERGYBALLVIEW_H

#include "../common/AnimatedSprite.h"
#include "../common/Window.h"
#include <string>
#include <yaml-cpp/yaml.h>
#define TEXTURES_EB_KEY "EnergyBall"
class EnergyBallView {
    Window& window;
    AnimatedSprite* animation;
    int energyBallWidth;
    int energyBallHeight;
    int xPos;
    int yPos;
public:
    EnergyBallView(Window &window, int xPos, int yPos, YAML::Node texturesData);
    ~EnergyBallView();
    void playAnimation();
    void move(int newPosX, int newPosY);
};


#endif //PORTAL_ENERGYBALLVIEW_H
