//
// Created by camix on 18/05/19.
//

#ifndef PORTAL_ROCKBLOCKBUTTON_H
#define PORTAL_ROCKBLOCKBUTTON_H

#include "MenuButton.h"

class RockBlockButton : public MenuButton {
public:
    RockBlockButton();

    explicit RockBlockButton(struct SDL_Rect* rect);
    ~RockBlockButton();
};


#endif //PORTAL_ROCKBLOCKBUTTON_H
