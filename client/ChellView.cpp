//
// Created by ndv on 5/14/19.
//

#include "ChellView.h"
#include <SDL.h>
#include <vector>
#include "../common/AnimatedSprite.h"
#include "SoundCodeQueue.h"
#include <string>
#include <yaml-cpp/yaml.h>

ChellView::ChellView(Window &window, int xPos, int yPos, int factor,
        SoundCodeQueue& queue,
        YAML::Node texturesData) :
            View(window, xPos, yPos, factor, CHELL_WIDTH, CHELL_HEIGHT),
            soundsQueue(queue),
            flip(SDL_FLIP_NONE) {
    deathCounterToStopDrawing = 1;
    runTimer = 0;
    YAML::Node animationsData = texturesData[TEXTURES_INFO_KEY];
    for (YAML::const_iterator it = animationsData.begin();
        it != animationsData.end(); ++it){
        YAML::Node node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int frames = node["frames"].as<int>();
        AnimatedSprite* newSprite = new AnimatedSprite(path, window, frames);
        // This is wrong, we should use a set Width and Height.
        animations.push_back(newSprite);
        if (name == "Death") {
            deathCounterToStopDrawing = frames * DEATH_COUNTER_MULTIPLIER;
        }
    }
    previousState = IDLE;
    currentState = IDLE;

}

ChellView::~ChellView() {
    for (auto it = animations.begin(); it != animations.end(); ++it){
        delete *it;
    }
}

void ChellView::playAnimation(const SDL_Rect& camera) {
    if (!checkCollisionWithCamera(camera)
        || deathCounterToStopDrawing == 0) return;

    int animationIndex = currentState;
    if (currentState == MOVING_RIGHT) {
        --animationIndex;
        flip = SDL_FLIP_NONE;
        if (updateRunTimer()) {
            soundsQueue.push(RUN_SOUND);
        }
    }
    if (currentState == MOVING_LEFT) {
        flip = SDL_FLIP_HORIZONTAL;
        if (updateRunTimer()) {
            soundsQueue.push(RUN_SOUND);
        }
    }
    if (currentState == JUMPING && previousState != currentState) {
        soundsQueue.push(JUMP_SOUND);
    }
    AnimatedSprite* animation = animations[animationIndex];
    if (currentState == DEAD){
        deathCounterToStopDrawing -= 1;
    }
    animation->draw(viewPosX - camera.x, viewPosY - camera.y, flip);
    animation->updateFrameStep();
}

void ChellView::setState(int state) {
    previousState = currentState;
    currentState = state;
}

bool ChellView::updateRunTimer() {
    bool retValue = false;
    if (runTimer + RUN_TIMESTEP < SDL_GetTicks()){
        runTimer = SDL_GetTicks();
        retValue = true;
    }
    return retValue;
}
