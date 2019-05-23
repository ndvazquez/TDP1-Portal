//
// Created by camix on 18/05/19.
//

#include "RockButton.h"
#define NAME "Rock1" //no esta definido igual aun.

RockButton::RockButton(struct SDL_Rect *rect, int rockNumber)  :
        MenuButton(rect, NAME, this->path[rockNumber]) {}

RockButton::~RockButton() {}
