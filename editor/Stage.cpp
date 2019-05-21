//
// Created by camix on 13/05/19.
//

#include "Stage.h"
#include "MouseButtonUp.h"
#include <iostream>
#include <yaml-cpp/yaml.h>

#define TEXTURE_CONFIG_FILE "editor/stage-textures-type.yaml"
#define Y 0
#define H this->window.getWindowHeight()
#define TOTAL_X this->window.getWindowWidth()
#define X (TOTAL_X)/this->xPortion
#define W (TOTAL_X) - (X)
#define MATRIX_TO_PIXEL_FACTOR 50
#define X_PIXEL(event) ((event).getX())
#define Y_PIXEL(event) ((event).getY())
#define X_PIXEL_TO_MATRIX_POSITION(xPixel) (((xPixel)  - X)/MATRIX_TO_PIXEL_FACTOR)
#define Y_PIXEL_TO_MATRIX_POSITION(yPixel) ((yPixel)/MATRIX_TO_PIXEL_FACTOR)


void setSDL_Rect(struct SDL_Rect* rect, int x, int y, int w, int h) {
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

Stage::Stage(Window& window, std::string& current, int xPortion):
    window(window), textures(YAML::LoadFile(TEXTURE_CONFIG_FILE)),
    stageView(window, textures, MATRIX_TO_PIXEL_FACTOR) , current(current),
    xPortion(xPortion) {
    this->me = (struct SDL_Rect*) malloc(sizeof(struct SDL_Rect*));
    this->setSize();
    this->camera = (struct SDL_Rect*) malloc(sizeof(struct SDL_Rect*));
    *this->camera = {0 ,0, W, H};
}

void Stage::setSize() {
    setSDL_Rect(this->me, X, Y, W, H);
}

Stage::~Stage() {
    delete(this->camera);
    delete(this->me);
}


void Stage::draw() {
//    std::cerr << "Entro a draaw" << std::endl;
    Sprite bgSprite("resources/editor-stage-bg.png", window);
    bgSprite.draw(window, this->me);
    stageView.draw(window, this->camera , X);

//    std::cerr << "Termino a draaw" << std::endl;
}

void Stage::handle(MouseButtonDown *event) {
    int xPixel = X_PIXEL(*event);
    int yPixel = Y_PIXEL(*event);
    int x = X_PIXEL_TO_MATRIX_POSITION(xPixel);
    int y = Y_PIXEL_TO_MATRIX_POSITION(yPixel);
    SDL_Point sdlPoint = {xPixel, yPixel};
    bool isIn = (bool) SDL_PointInRect(&sdlPoint, this->me);
    if (!isIn) {
        return;
    }
    try {
        current = stageView.getName(x, y);
    }
    catch (EditorStageViewEmptyPositionException) {
        return;
    }
    stageView.removeTile(x,y);
}

void Stage::handle(MouseButtonUp *event) {

    int xPixel = X_PIXEL(*event);
    int yPixel = Y_PIXEL(*event);
    int x = X_PIXEL_TO_MATRIX_POSITION(xPixel);
    int y = Y_PIXEL_TO_MATRIX_POSITION(yPixel);
    SDL_Point sdlPoint = {xPixel, yPixel};
    bool isIn = (bool) SDL_PointInRect(&sdlPoint, this->me);
    if (!isIn ) {
        return;
    }
    try {
        stageView.addTile(x, y, current);
    }
    catch (EditorStageException) {
        return;
    }
    current = "";
}