//
// Created by ndv on 5/30/19.
//

#include "PortalView.h"

PortalView::PortalView(Window &window, int xPos, int yPos,
        int factor, YAML::Node texturesData) :
        View(window, xPos, yPos, factor, PORTAL_WIDTH, PORTAL_HEIGHT),
        flip(SDL_FLIP_NONE){
    YAML::Node spritesData = texturesData[TEXTURES_PORTAL_KEY];
    for (YAML::const_iterator it = spritesData.begin();
         it != spritesData.end(); ++it) {
        YAML::Node node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        int totalFrames = node["frames"].as<int>();
        AnimatedSprite *newSprite = new AnimatedSprite(path, window, totalFrames);
        sprites[name] = newSprite;
    }
    currentSprite = PORTAL_BLUE;
}

PortalView::~PortalView() {
    for (auto it = sprites.begin(); it != sprites.end(); ++it){
        delete it->second;
    }
}

//TODO: Determinar de alguna forma qué FLIP usar.
void PortalView::playAnimation(SDL_Rect &camera) {
    if (!checkCollisionWithCamera(camera)) return;
    AnimatedSprite* sprite = sprites[currentSprite];
    sprite->draw(viewPosX - camera.x, viewPosY - camera.y, flip);
}

void PortalView::changePortalColor() {
    currentSprite = currentSprite == PORTAL_BLUE ? PORTAL_ORANGE : PORTAL_BLUE;
}
