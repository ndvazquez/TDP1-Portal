//
// Created by ndv on 6/14/19.
//

#ifndef PORTAL_GATEVIEW_H
#define PORTAL_GATEVIEW_H

#include <yaml-cpp/yaml.h>
#include "../../common/Window.h"
#include "../../common/AnimatedSprite.h"
#include "View.h"
#include "../../common/constants.h"

#define TEXTURES_GATE_KEY "Gate"
#define GATE_CLOSED 1
#define GATE_OPEN 0

class GateView : public View {
    AnimatedSprite* animation;
    int previousState;
    int currentState;
    bool transitionAnimation;
    int frameCounter;
    int lastFrame;
public:
    GateView(Window &window,
    int xPos,
    int yPos,
    int factor,
            YAML::Node& texturesData);
    ~GateView();
    void playAnimation(const SDL_Rect& camera);
    void setState(int state);
};


#endif //PORTAL_GATEVIEW_H
