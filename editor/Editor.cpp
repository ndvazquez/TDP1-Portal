//
// Created by camix on 15/05/19.
//

#include "Editor.h"
#include "MouseButtonDown.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600



Editor::Editor(Window& window) : window(window), stage(window, current, WIDTH_PROPORTION), menu(window, current) {
    this->current = INVALID_CURRENT;
}

Editor::~Editor() {}

void Editor::draw() {

    //std::cerr << "hola, dibuja \n";
    window.clear();
    //std::cerr << "window.clear \n";
    menu.draw();
    //std::cerr << "menu.draw \n";
    stage.draw();
    //std::cerr << "stage.draw \n";
    window.render();
    //std::cerr << "window.render \n";
}

void Editor::handle(MouseButtonDown* event) {
    this->menu.handle(event);
    this->stage.handle(event);
}

void Editor::handle(MouseButtonUp *event) {
    this->menu.handle(event);
    this->stage.handle(event);
}
