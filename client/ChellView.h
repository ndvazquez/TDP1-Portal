//
// Created by ndv on 5/14/19.
//

#ifndef PORTAL_CHELLVIEW_H
#define PORTAL_CHELLVIEW_H

#include <unordered_map>
#include <SDL.h>
#include "../common/AnimatedSprite.h"
#include <string>
#include <yaml-cpp/yaml.h>

#define TEXTURES_INFO_KEY "Chell"
#define CHELL_RUN "Run"
#define CHELL_RESTING_IDLE "RestingIdle"
#define CHELL_JUMPING "Jumping"

class ChellView {
    Window& gameWindow;
    int chellWidth;
    int chellHeight;
    int xPos;
    int yPos;
    bool isJumping;
    SDL_RendererFlip flip;
    std::string currentAnimation;
    std::unordered_map<std::string, AnimatedSprite*> animations;

public:
    ChellView(Window &window, int xPos, int yPos, YAML::Node texturesData);
    ~ChellView();
    void playAnimation(SDL_Rect& camera);
    void changeJumpingStatus(bool isChellJumping);
    void handleEvent(SDL_Event& e, const Uint8* keys);
    void move(int newPosX, int newPosY);
    // This method is only used by the playable Chell;
    void updateCamera(SDL_Rect& camera, int levelWidth, int levelHeight);
};


#endif //PORTAL_CHELLVIEW_H
