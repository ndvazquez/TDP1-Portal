//
// Created by camix on 15/05/19.
//

#ifndef TDP1_PORTAL_EDITO_H
#define TDP1_PORTAL_EDITO_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "../common/SDLSession.h"
#include "../common/Window.h"
#include "Stage.h"
#include "Menu.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define INVALID_CURRENT -1



class Editor {
private:
    int8_t current;
    Menu menu(current, 800/11, SCREEN_HEIGHT);
    Stage stage(current, 800 - 800/11);
    Window window("Editor", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

public:
    Editor();
    ~Editor();
    void draw();
};


#endif //TDP1_PORTAL_EDITO_H
