//
// Created by ndv on 5/27/19.
//

#include "ButtonView.h"
#include <string>

ButtonView::ButtonView(Window &window, int xPos, int yPos, int factor,
        YAML::Node& texturesData) :
        View(window, xPos, yPos, factor, BUTTON_WIDTH, BUTTON_HEIGHT) {
    YAML::Node spritesData = texturesData[TEXTURES_BUTTON_KEY];
    for (YAML::const_iterator it = spritesData.begin();
         it != spritesData.end(); ++it) {
        YAML::Node node = *it;
        int buttonState = node["name"].as<int>();
        std::string path = node["path"].as<std::string>();
        Sprite *newSprite = new Sprite(path, window);
        sprites[buttonState] = newSprite;
    }
    buttonState = BUTTON_STATE_OFF;
}

ButtonView::~ButtonView() {
    for (auto it = sprites.begin(); it != sprites.end(); ++it){
        delete it->second;
    }
}

void ButtonView::setState(int state) {
    buttonState = state;
}

void ButtonView::playAnimation(const SDL_Rect &camera) {
    if (!checkCollisionWithCamera(camera)) return;
    Sprite* sprite = sprites[buttonState];
    // We'll resize the button sprite to make it fit over two blocks.
    SDL_Rect destRect = {viewPosX - camera.x,
                         viewPosY - camera.y,
                         int(viewWidthInMeters * mtpFactor),
                         int(viewHeightInMeters * mtpFactor)};;
    sprite->draw(&destRect);
}
