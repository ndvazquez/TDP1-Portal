//
// Created by camix on 18/05/19.
//

#ifndef PORTAL_METALBLOCKBUTTON_H
#define PORTAL_METALBLOCKBUTTON_H

#include <SDL.h>
#include <SDL_image.h>
#include "MenuButton.h"


class MetalBlockButton : public MenuButton {
public:
    MetalBlockButton();

    explicit MetalBlockButton(struct SDL_Rect* rect);
    ~MetalBlockButton();
};


#endif //PORTAL_METALBLOCKBUTTON_H
