//
// Created by ndv on 6/11/19.
//

#ifndef PORTAL_CAKEVIEW_H
#define PORTAL_CAKEVIEW_H

#include <yaml-cpp/node/node.h>
#include "../../common/Window.h"
#include "../../common/AnimatedSprite.h"
#include "View.h"
#include "../../common/constants.h"

#define TEXTURES_CAKE_KEY "Cake"

class CakeView : public View {
    AnimatedSprite* animation;
public:
    CakeView(Window &window,
    int xPos,
    int yPos,
    int factor,
            YAML::Node texturesData);
    ~CakeView();
    void playAnimation(const SDL_Rect& camera);
    void setState(int state);
};


#endif //PORTAL_CAKEVIEW_H
