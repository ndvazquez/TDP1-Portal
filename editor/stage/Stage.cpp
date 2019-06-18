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
#define X_PIXEL_TO_MATRIX_POSITION(xPixel) (((xPixel)  - X_START)/MATRIX_TO_PIXEL_FACTOR) + this->camera.x
#define Y_PIXEL_TO_MATRIX_POSITION(yPixel) (((yPixel) - Y_START)/MATRIX_TO_PIXEL_FACTOR) + this->camera.y


Stage::Stage(Window &window, int *current, int yPortion):
    window(window), textures(YAML::LoadFile(TEXTURE_CONFIG_FILE)),
    controller(window, textures, MATRIX_TO_PIXEL_FACTOR) , current(current),
    yPortion(yPortion) {
    this->me = {X_START, Y_START, W, H};
    this->camera = {0 ,0, W, H};
}


Stage::~Stage() {
    //delete(this->camera);
    //delete(this->me);
}

void Stage::pixelToMatrix(MouseButton &event,
                          int *xPixel, int *yPixel, int *x, int *y) {
    *xPixel = X_PIXEL(event);
    *yPixel = Y_PIXEL(event);
    *x = X_PIXEL_TO_MATRIX_POSITION(*xPixel);
    *y = Y_PIXEL_TO_MATRIX_POSITION(*yPixel);
    SDL_Point sdlPoint = {*xPixel, *yPixel};
    if (! (bool) SDL_PointInRect(&sdlPoint, &this->me)) {
        throw StageNotInsideMeException();
    }
}

void Stage::draw(int x, int y) {
    Sprite bgSprite("resources/editor-stage-bg.png", window);
    bgSprite.draw(&this->me);
    controller.draw(&this->camera , Y_START);
    // draw the selected object.

    SDL_Point sdlPoint = {x, y};
    if (! (bool) SDL_PointInRect(&sdlPoint, &this->me)) {
       return;
    }
    x = (X_PIXEL_TO_MATRIX_POSITION(x)) - this->camera.x;
    y = (Y_PIXEL_TO_MATRIX_POSITION(y)) - this->camera.y;
    controller.drawCurrent(*current, x, y);

}


void Stage::handleMouseButtonDown(MouseButton& event) {
    int xPixel, yPixel, x, y;
    try {
        pixelToMatrix(event, &xPixel, &yPixel, &x, &y);
        *current = controller.getName(x, y);
        controller.removeTile(x,y);
    }
    catch (StageControllerException& e) {
        std::cerr << "Estoy empty" << std::endl;
        *current = EMPTY;
        return;
    }
    catch(StageNotInsideMeException& e) {
        return;
    }
}

void Stage::handleMouseButtonUp(MouseButton& event) {
    int xPixel, yPixel, x, y;
    try {
        pixelToMatrix(event, &xPixel, &yPixel, &x, &y);
        controller.addTile(x, y, *current);
        *current = EMPTY;
    }
    catch (StageControllerException& e) {
        *current = EMPTY;
        return;
    }
    catch(StageNotInsideMeException& e) {
        return;
    }
}

void Stage::handleMouseDoubleClick(MouseButton &event) {
    int xPixel, yPixel, x, y;
    try {
        pixelToMatrix(event, &xPixel, &yPixel, &x, &y);
    }
    catch(StageNotInsideMeException& e) {
        return;
    }
    std::string enteredName;
    std::cerr << "Ingrese un nombre para su objeto." << std::endl;
    std::getline(std::cin, enteredName);

    std::cerr << "El nombre ingresado es: " << enteredName << std::endl;
    controller.nameAnObject(x,y, enteredName);
}

void Stage::handleMouseRightClick(MouseButton &event) {
    int xPixel, yPixel, x, y;
    try {
        pixelToMatrix(event, &xPixel, &yPixel, &x, &y);
        controller.addCondition(x, y);
    }
    catch(StageNotInsideMeException& e) {
        return;
    }
}

void Stage::handleLeft() {
    if(!this->camera.x) return;
    this->camera.x --;
}

void Stage::handleRight() {
    this->camera.x ++;
}

void Stage::handleUp() {
    if(!this->camera.y) return;
    this->camera.y --;
}

void Stage::handleDown() {
    this->camera.y ++;
}

void Stage::close() {
    controller.writeYaml(Y_END);
}
