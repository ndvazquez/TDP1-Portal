//
// Created by camix on 13/05/19.
//

#ifndef PORTAL_MENU_H
#define PORTAL_MENU_H

#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "../common/Window.h"
#include "../common/Sprite.h"

#define WIDTH_PROPORTION 10


class Menu {
private:
    Window& window;
//uint8_t& current;
    std::vector<struct SDL_Rect*> options;
    struct SDL_Rect* me;
    void set();

public:
    //Menu()
    explicit Menu(Window &window);
    ~Menu();
    void draw();
};


#endif //PORTAL_MENU_H
