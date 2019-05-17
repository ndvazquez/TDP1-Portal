//
// Created by camix on 15/05/19.
//

#include "Editor.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600



Editor::Editor(Window& window) : window(window), menu(window), stage(window, current, WIDTH_PROPORTION) {
    this->current = INVALID_CURRENT;
}

Editor::~Editor() {}

void Editor::draw() {
    current = std::string("RockBlock");
    stage.insert(0,0);
    window.clear();
    menu.draw();
    stage.draw();
    window.render();
}
