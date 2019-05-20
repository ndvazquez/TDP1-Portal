//
// Created by camix on 18/05/19.
//

#include "RockBlockButton.h"

#define NAME "RockBlock"
#define PATH "resources/blocks/rock-block.png"

RockBlockButton::RockBlockButton(struct SDL_Rect* rect) :
        MenuButton(rect, NAME, PATH) {}

RockBlockButton::RockBlockButton() :
        MenuButton(NULL, NAME, PATH) {}

RockBlockButton::~RockBlockButton() {}
