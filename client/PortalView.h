//
// Created by ndv on 5/30/19.
//

#ifndef PORTAL_PORTALVIEW_H
#define PORTAL_PORTALVIEW_H

#include <yaml-cpp/yaml.h>
#include "../common/Window.h"
#include "../common/AnimatedSprite.h"
#include "View.h"
#include "../common/constants.h"
#include <unordered_map>
#include <string>

#define TEXTURES_PORTAL_KEY "Portal"
#define PORTAL_BLUE "Blue"
#define PORTAL_ORANGE "Orange"
#define PORTAL_VERTICAL 0
#define PORTAL_HORIZONTAL 1
#define PORTAL_ROTATION_ANGLE 90

class PortalView : public View {
    std::unordered_map<std::string, AnimatedSprite*> sprites;
    std::string currentSprite;
    int angle;
public:
    PortalView(Window &window,
            int xPos,
            int yPos,
            int factor,
            YAML::Node texturesData);
    ~PortalView();
    void playAnimation(const SDL_Rect& camera);
    void setState(int state);
};


#endif //PORTAL_PORTALVIEW_H
