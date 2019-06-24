//
// Created by ndv on 6/24/19.
//

#ifndef PORTAL_PINTOOL_H
#define PORTAL_PINTOOL_H

#include <yaml-cpp/yaml.h>
#include "View.h"
#include "../../common/Sprite.h"
#include "../../common/constants.h"
#define TEXTURES_PIN_KEY "Pintool"

class PintoolView : public View {
    Sprite* sprite;
public:
    PintoolView(Window &window,
             int xPos,
             int yPos,
             int factor,
             YAML::Node& texturesData);
    ~PintoolView();
    void playAnimation(const SDL_Rect& camera);
    void setState(int state);
};


#endif //PORTAL_PINTOOL_H
