//
// Created by ndv on 5/13/19.
//

#include "StageView.h"
#include "Sprite.h"
#include <iostream>
#include "yaml-cpp/yaml.h"

StageView::StageView(Window& window, YAML::Node& texturesInfo) {
    const YAML::Node& staticObjects = texturesInfo[TEXTURES_KEY];
    for (YAML::const_iterator it = staticObjects.begin();
    it != staticObjects.end(); ++it){
        const YAML::Node& node = *it;
        std::string name = node["name"].as<std::string>();
        std::string path = node["path"].as<std::string>();
        Sprite* newSprite = new Sprite(path, window);
        textures[name] = newSprite;
    }
}

StageView::~StageView() {
    for (auto it = textures.begin(); it != textures.end(); ++it){
        delete it->second;
    }
}

void StageView::draw(Window& window){
    int windowHeight = window.getWindowHeight();
    Sprite* sprite = textures["MetalBlock"];
    int yStartingPos = windowHeight - sprite->getHeight();

    SDL_Rect destRect = { 0, yStartingPos, sprite->getWidth(), sprite->getHeight()};
    sprite->draw(window, &destRect);
    destRect.x += sprite->getWidth();
    sprite->draw(window, &destRect);
    destRect.x += sprite->getWidth();
    sprite->draw(window, &destRect);
    destRect.x += sprite->getWidth();
    sprite->draw(window, &destRect);
    destRect.x += sprite->getWidth();
    sprite->draw(window, &destRect);
    destRect.x += sprite->getWidth();
    sprite->draw(window, &destRect);
    destRect.x += sprite->getWidth();
    sprite->draw(window, &destRect);
}
