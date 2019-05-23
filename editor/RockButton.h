//
// Created by camix on 18/05/19.
//

#ifndef PORTAL_ROCKBUTTON_H
#define PORTAL_ROCKBUTTON_H

#include "MenuButton.h"
#include <vector>

#define ROCK1_PATH "resources/rocks/1.png"
#define ROCK2_PATH "resources/rocks/2.png"
#define ROCK3_PATH "resources/rocks/3.png"

class RockButton : public MenuButton {
private:
    std::vector<std::string> path = {ROCK1_PATH, ROCK2_PATH, ROCK1_PATH};

public:
    explicit RockButton(struct SDL_Rect* rect, int rockNumber);
    ~RockButton();
};


#endif //PORTAL_ROCKBUTTON_H
