//
// Created by camix on 13/05/19.
//

#include <iostream>
#include <yaml-cpp/yaml.h>
#include "Stage.h"



#define TEXTURE_CONFIG_FILE "editor/textures-info.yaml"

#define Y_END this->window.getWindowHeight() - this->window.getWindowHeight()/this->yPortion
#define Y_START 0
#define X_START 0
#define X_END this->window.getWindowWidth()
#define H (Y_END) - (Y_START)
#define W (X_END) - (X_START)

#define MATRIX_TO_PIXEL_FACTOR 50
#define X_PIXEL(event) ((event).getX())
#define Y_PIXEL(event) ((event).getY())
#define X_PIXEL_TO_MATRIX_POSITION(xPixel) (((xPixel)  - X_START)/MATRIX_TO_PIXEL_FACTOR)
#define Y_PIXEL_TO_MATRIX_POSITION(yPixel) (((yPixel) - Y_START)/MATRIX_TO_PIXEL_FACTOR)


void setSDL_Rect(struct SDL_Rect* rect, int x, int y, int w, int h) {
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

Stage::Stage(Window& window, std::string& current, int yPortion):
    window(window), textures(YAML::LoadFile(TEXTURE_CONFIG_FILE)),
    controller(window, textures, MATRIX_TO_PIXEL_FACTOR) , current(current),
    yPortion(yPortion) {
    this->me = (struct SDL_Rect*) malloc(sizeof(struct SDL_Rect*));
    this->setSize();
    this->camera = (struct SDL_Rect*) malloc(sizeof(struct SDL_Rect*));
    *this->camera = {0 ,0, W, H};
}

void Stage::setSize() {
    setSDL_Rect(this->me, X_START, Y_START, W, H);
}

Stage::~Stage() {
    delete(this->camera);
    delete(this->me);
}


void Stage::draw() {
    Sprite bgSprite("resources/editor-stage-bg.png", window);
    bgSprite.draw(this->me);
    controller.draw(this->camera , Y_START);
}

void Stage::handleMouseButtonDown(MouseButton& event) {
    int xPixel = X_PIXEL(event);
    int yPixel = Y_PIXEL(event);
    int x = X_PIXEL_TO_MATRIX_POSITION(xPixel);
    int y = Y_PIXEL_TO_MATRIX_POSITION(yPixel);
    SDL_Point sdlPoint = {xPixel, yPixel};
    bool isIn = (bool) SDL_PointInRect(&sdlPoint, this->me);
    if (!isIn) {
        return;
    }
    try {
        current = controller.getName(x, y);
        controller.removeTile(x,y);
    }
    catch (StageControllerException& e) {
        current = "";
        return;
    }
}

void Stage::handleMouseButtonUp(MouseButton& event) {
    int xPixel = X_PIXEL(event);
    int yPixel = Y_PIXEL(event);
    int x = X_PIXEL_TO_MATRIX_POSITION(xPixel);
    int y = Y_PIXEL_TO_MATRIX_POSITION(yPixel);
    SDL_Point sdlPoint = {xPixel, yPixel};
    bool isIn = (bool) SDL_PointInRect(&sdlPoint, this->me);
    if (!isIn ) {
        return;
    }
    try {
        controller.addTile(x, y, current);
        current = "";
    }
    catch (StageControllerException& e) {
        return;
    }
}
void Stage::handleMouseDoubleClick(MouseButton &event) {
    int xPixel = X_PIXEL(event);
    int yPixel = Y_PIXEL(event);
    int x = X_PIXEL_TO_MATRIX_POSITION(xPixel);
    int y = Y_PIXEL_TO_MATRIX_POSITION(yPixel);
    SDL_Point sdlPoint = {xPixel, yPixel};
    bool isIn = (bool) SDL_PointInRect(&sdlPoint, this->me);
    if (!isIn) {
        return;
    }
    std::string enteredName;
    std::cerr << "Ingrese un nombre para su objeto." << std::endl;
    std::getline(std::cin, enteredName);

    std::cerr << "El nombre ingresado es: " << enteredName << std::endl;
    controller.nameAnObject(x,y, enteredName);
}

void Stage::handleMouseRightClick(MouseButton &event) {
    int xPixel = X_PIXEL(event);
    int yPixel = Y_PIXEL(event);
    int x = X_PIXEL_TO_MATRIX_POSITION(xPixel);
    int y = Y_PIXEL_TO_MATRIX_POSITION(yPixel);
    SDL_Point sdlPoint = {xPixel, yPixel};
    bool isIn = (bool) SDL_PointInRect(&sdlPoint, this->me);
    if (!isIn) {
        return;
    }
    std::cerr << "Ingrese una condición lógica." << std::endl;

    std::string enteredCondition;
    std::getline(std::cin, enteredCondition);

    std::cerr << "El nombre ingresado es: " << enteredCondition << std::endl;
    controller.addCondition(x, y, enteredCondition);
}

