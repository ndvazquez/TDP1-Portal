//
// Created by camix on 18/05/19.
//

#include "MetalBlockButton.h"

#define NAME "MetalBlock"
#define PATH "resources/blocks/metal-block.png"

MetalBlockButton::MetalBlockButton(struct SDL_Rect *rect)  :
        MenuButton(rect, NAME, PATH) {}

MetalBlockButton::MetalBlockButton() :
        MenuButton(NULL, NAME, PATH) {}

MetalBlockButton::~MetalBlockButton() {}

