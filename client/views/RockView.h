//
// Created by ndv on 5/26/19.
//

#ifndef PORTAL_ROCKVIEW_H
#define PORTAL_ROCKVIEW_H

#include <yaml-cpp/yaml.h>
#include "View.h"
#include "../../common/Sprite.h"
#include "../../common/constants.h"
//TODO: Hacer que esto sea un random choice entre los tres sprites de Rock.
#define TEXTURES_ROCK_KEY "Rock"

class RockView : public View {
    Sprite* sprite;
public:
    RockView(Window &window,
            int xPos,
            int yPos,
            int factor,
            YAML::Node& texturesData);
    ~RockView();
    void playAnimation(const SDL_Rect& camera);
    void setState(int state);
};


#endif //PORTAL_ROCKVIEW_H
