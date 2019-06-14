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
#include "SoundCodeQueue.h"

#define TEXTURES_INFO_KEY "Chell"
#define DEATH_COUNTER_MULTIPLIER 120
#define RUN_TIMESTEP 350
#define IDLE 0
#define JUMPING 1
#define DEAD 2
#define WINNER 3
#define MOVING_LEFT 4
#define MOVING_RIGHT 5

class ChellView : public View {
    SoundCodeQueue& soundsQueue;
    SDL_RendererFlip flip;
    int previousState;
    int currentState;
    std::vector<AnimatedSprite*> animations;
    int deathCounterToStopDrawing;
    int runTimer;
    bool updateRunTimer();
public:
    ChellView(Window &window,
            int xPos,
            int yPos,
            int factor,
            SoundCodeQueue& queue,
            YAML::Node texturesData);
    ~ChellView();
    void playAnimation(const SDL_Rect& camera);
    void setState(int state);
};


#endif //PORTAL_CHELLVIEW_H
