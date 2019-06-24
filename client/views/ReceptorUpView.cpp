//
// Created by ndv on 6/23/19.
//

#include "ReceptorUpView.h"
#include <string>

ReceptorUpView::ReceptorUpView(Window &window, int xPos, int yPos, int factor,
                       YAML::Node texturesData) :
        View(window, xPos, yPos, factor, RECEPTOR_WIDTH, RECEPTOR_HEIGHT) {
    YAML::Node spritesData = texturesData[TEXTURES_ER_UP_KEY];
    for (YAML::const_iterator it = spritesData.begin();
         it != spritesData.end(); ++it) {
        YAML::Node node = *it;
        int buttonState = node["name"].as<int>();
        std::string path = node["path"].as<std::string>();
        Sprite *newSprite = new Sprite(path, window);
        sprites[buttonState] = newSprite;
    }
    receptorState = RECEPTOR_STATE_OFF;
}

ReceptorUpView::~ReceptorUpView() {
    for (auto it = sprites.begin(); it != sprites.end(); ++it){
        delete it->second;
    }
}

void ReceptorUpView::setState(int state) {
    receptorState = state;
}

void ReceptorUpView::playAnimation(const SDL_Rect &camera) {
    if (!checkCollisionWithCamera(camera)) return;
    Sprite* sprite = sprites[receptorState];
    SDL_Rect destRect = {viewPosX - camera.x,
                         viewPosY - camera.y,
                         int(viewWidthInMeters * mtpFactor),
                         int(viewHeightInMeters * mtpFactor)};;
    sprite->draw(&destRect);
}
