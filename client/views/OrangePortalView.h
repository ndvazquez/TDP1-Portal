//
// Created by ndv on 6/13/19.
//

#ifndef PORTAL_ORANGEPORTALVIEW_H
#define PORTAL_ORANGEPORTALVIEW_H

#include <yaml-cpp/yaml.h>
#include "../../common/Window.h"
#include "../../common/AnimatedSprite.h"
#include "View.h"
#include "../../common/constants.h"
#include <string>

#define TEXTURES_ORANGE_PORTAL_KEY "OrangePortal"
#define PORTAL_VERTICAL 1
#define PORTAL_HORIZONTAL 0

class OrangePortalView : public View {
    AnimatedSprite* animation;
public:
    OrangePortalView(Window &window,
                   int xPos,
                   int yPos,
                   int factor,
                   YAML::Node& texturesData);
    ~OrangePortalView();
    void playAnimation(const SDL_Rect& camera);
    void setState(int state);
};

#endif //PORTAL_ORANGEPORTALVIEW_H
