//
// Created by ndv on 5/27/19.
//

#include "ButtonView.h"

ButtonView::ButtonView(Window &window, int xPos, int yPos, int factor,
        YAML::Node texturesData) :
        View(window, xPos, yPos, factor, BUTTON_WIDTH, BUTTON_HEIGHT) {
    YAML::Node spritesData = texturesData[TEXTURES_BUTTON_KEY];
    for (YAML::const_iterator it = spritesData.begin();
         it != spritesData.end(); ++it) {
        YAML::Node node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        Sprite *newSprite = new Sprite(path, window);
        // This is wrong, we should use a set Width and Height.
        sprites[name] = newSprite;
    }
    currentSprite = BUTTON_STATE_OFF;

}

ButtonView::~ButtonView() {
    for (auto it = sprites.begin(); it != sprites.end(); ++it){
        delete it->second;
    }
}

void ButtonView::changeButtonState() {
    currentSprite = currentSprite == BUTTON_STATE_OFF ? BUTTON_STATE_ON : BUTTON_STATE_OFF;
}

void ButtonView::playAnimation(SDL_Rect &camera) {
    if (!checkCollisionWithCamera(camera)) return;
    Sprite* sprite = sprites[currentSprite];
    // We'll resize the button sprite to make it fit over two blocks.
    SDL_Rect destRect = {viewPosX - camera.x, viewPosY - camera.y, mtpFactor * 2, mtpFactor / 2};
    sprite->draw(&destRect);
}
