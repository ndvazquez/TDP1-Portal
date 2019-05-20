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
#include "MenuButton.h"
#include "MouseButtonDown.h"
#include "MouseButtonUp.h"

#define WIDTH_PROPORTION 10


class Menu {
private:
    Window& window;
    std::string& current;
    std::vector<MenuButton*> options;
    struct SDL_Rect* me;
    void set();

public:
    //Menu()
    explicit Menu(Window &window, std::string& current);
    ~Menu();
    void draw();



    void handle(MouseButtonDown *event);

    void handle(MouseButtonUp *event);
};


#endif //PORTAL_MENU_H
