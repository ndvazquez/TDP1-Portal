//
// Created by ndv on 5/14/19.
//

#ifndef PORTAL_CHELLVIEW_H
#define PORTAL_CHELLVIEW_H

#include <SDL.h>
#include "../common/AnimatedSprite.h"
#include <string>
#include <yaml-cpp/yaml.h>
#include "View.h"
#include <vector>
#include "../common/constants.h"
#define TEXTURES_INFO_KEY "Chell"
#define DEATH_COUNTER_MULTIPLIER 120
class ChellView : public View {
    SDL_RendererFlip flip;
    State currentState;
    std::vector<AnimatedSprite*> animations;
    int deathCounterToStopDrawing;
public:
    ChellView(Window &window, int xPos, int yPos, int factor, YAML::Node texturesData);
    ~ChellView();
    void playAnimation(const SDL_Rect& camera);
    // This method is only used by the playable Chell;
    int getCenterPosX();
    int getCenterPosY();
    void setState(State state);
};


#endif //PORTAL_CHELLVIEW_H
