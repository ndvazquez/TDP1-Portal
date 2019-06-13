//
// Created by camix on 15/05/19.
//

#ifndef TDP1_PORTAL_EDITOR_H
#define TDP1_PORTAL_EDITOR_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "../common/SDLSession.h"
#include "../common/Window.h"
#include "stage/Stage.h"
#include "Menu.h"
#include "Event.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define INVALID_CURRENT ""



class Editor {
private:
    std::string current;
    Window& window;
    Stage stage;
    Menu menu;

public:
    explicit Editor(Window& window);
    ~Editor();
    void draw();
    void handleMouseButtonUp(SDL_Event* event);
    void handleMouseButtonDown(SDL_Event* event);

    void handleMouseDoubleClick(SDL_Event *event);
    void handleMouseRightClick(SDL_Event *event);

};


#endif //TDP1_PORTAL_EDITO_H
