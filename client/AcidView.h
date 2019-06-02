//
// Created by ndv on 5/23/19.
//

#ifndef PORTAL_ACIDVIEW_H
#define PORTAL_ACIDVIEW_H


#include <yaml-cpp/node/node.h>
#include "../common/Window.h"
#include "../common/AnimatedSprite.h"
#include "View.h"
#include "../common/constants.h"

#define TEXTURES_ACID_KEY "Acid"

class AcidView : public View{
    AnimatedSprite* animation;
public:
    AcidView(Window &window, int xPos, int yPos, int factor, YAML::Node texturesData);
    ~AcidView();
    void playAnimation(const SDL_Rect& camera);
};


#endif //PORTAL_ACIDVIEW_H
