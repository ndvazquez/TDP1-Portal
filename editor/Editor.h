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
#include "Event.h"
#include "MouseButtonDown.h"
#include "MouseButtonUp.h"

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
    void handle(MouseButtonUp *event);
    void handle(MouseButtonDown *event);
};


#endif //TDP1_PORTAL_EDITO_H
