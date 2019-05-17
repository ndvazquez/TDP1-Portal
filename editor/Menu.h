//
// Created by camix on 13/05/19.
//

#ifndef PORTAL_MENU_H
#define PORTAL_MENU_H

#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "../common/Window.h"


class Menu {
private:
    uint8_t& current;
    uint32_t xEnd;
    uint32_t yEnd;
    std::vector<struct SDL_Rect*> options;
    std::vector<Sprite> images;
    //struct SDL_Rect me;

public:
    Menu();
    ~Menu();
    void draw(Window& window);
};


#endif //PORTAL_MENU_H
