//
// Created by camix on 15/05/19.
//

#include "Editor.h"
#include "MouseButtonDown.h"
#include "MouseDoubleCick.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


Editor::Editor(Window& window) : window(window), stage(window, current, WIDTH_PROPORTION), menu(window, current) {
    this->current = INVALID_CURRENT;
}

Editor::~Editor() {}

void Editor::draw() {
    window.clear();
    menu.draw();
    stage.draw();
    window.render();
}

void Editor::handleMouseButtonDown(SDL_Event* event) {
    MouseButtonDown e(event);
    this->menu.handle(e);
    this->stage.handle(e);
}

void Editor::handleMouseDoubleCick(SDL_Event *event) {
    MouseDoubleCick e(event);
    this->stage.handle(e);
}

void Editor::handleMouseButtonUp(SDL_Event *event) {
    MouseButtonUp e(event);
    this->menu.handle(e);
    this->stage.handle(e);
}
