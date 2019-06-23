//
// Created by ndv on 5/30/19.
//

#ifndef PORTAL_BLUEPORTALVIEW_H
#define PORTAL_BLUEPORTALVIEW_H

#include <yaml-cpp/yaml.h>
#include "../../common/Window.h"
#include "../../common/AnimatedSprite.h"
#include "View.h"
#include "../../common/constants.h"
#include <string>

#define TEXTURES_BLUE_PORTAL_KEY "BluePortal"
#define PORTAL_VERTICAL 1
#define PORTAL_HORIZONTAL 0

class BluePortalView : public View {
    AnimatedSprite* animation;
public:
    BluePortalView(Window &window,
            int xPos,
            int yPos,
            int factor,
            YAML::Node texturesData);
    ~BluePortalView();
    void playAnimation(const SDL_Rect& camera);
    void setState(int state);
};


#endif //PORTAL_BLUEPORTALVIEW_H
