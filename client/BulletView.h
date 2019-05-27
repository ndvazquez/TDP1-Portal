//
// Created by ndv on 5/23/19.
//

#ifndef PORTAL_BULLETVIEW_H
#define PORTAL_BULLETVIEW_H


#include <yaml-cpp/yaml.h>
#include "../common/Window.h"
#include "../common/AnimatedSprite.h"
#include "View.h"

#define TEXTURES_BULLET_KEY "Bullet"
#define FRAMERATE_ADJUSTMENT 2

class BulletView : public View {
    AnimatedSprite* animation;
public:
    BulletView(Window &window, int xPos, int yPos, int factor, YAML::Node texturesData);
    ~BulletView();
    void playAnimation();
    void playAnimation(double angle);
};

#endif //PORTAL_BULLETVIEW_H
