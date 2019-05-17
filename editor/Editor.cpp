//
// Created by camix on 15/05/19.
//

#include "Editor.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define INVALID_CURRENT -1


Editor::Editor() {
    this->current = INVALID_CURRENT;
}

Editor::~Editor() {}

void Editor::draw() {
    menu.draw(window);
    stage.draw(window);
}
