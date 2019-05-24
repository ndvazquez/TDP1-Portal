//
// Created by ndv on 5/23/19.
//

#ifndef PORTAL_BULLETVIEW_H
#define PORTAL_BULLETVIEW_H


#include <yaml-cpp/yaml.h>
#include "../common/Window.h"
#include "../common/AnimatedSprite.h"

#define TEXTURES_BULLET_KEY "Bullet"
#define FRAMERATE_ADJUSTMENT 2

class BulletView {
    Window& window;
    AnimatedSprite* animation;
    int bulletWidth;
    int bulletHeight;
    int xPos;
    int yPos;
public:
    BulletView(Window &window, int xPos, int yPos, YAML::Node texturesData);
    ~BulletView();
    void playAnimation(double angle);
    void move(int newPosX, int newPosY);
};


#endif //PORTAL_BULLETVIEW_H
