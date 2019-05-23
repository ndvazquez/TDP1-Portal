//
// Created by ndv on 5/23/19.
//

#ifndef PORTAL_ACIDVIEW_H
#define PORTAL_ACIDVIEW_H


#include <yaml-cpp/node/node.h>
#include "../common/Window.h"
#include "../common/AnimatedSprite.h"

#define TEXTURES_ACID_KEY "Acid"

class AcidView {
    Window& window;
    AnimatedSprite* animation;
    int acidWidth;
    int acidHeight;
    int xPos;
    int yPos;
public:
    AcidView(Window &window, int xPos, int yPos, YAML::Node texturesData);
    ~AcidView();
    void playAnimation();
    void move(int newPosX, int newPosY);
};


#endif //PORTAL_ACIDVIEW_H
