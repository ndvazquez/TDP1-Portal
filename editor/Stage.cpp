//
// Created by camix on 13/05/19.
//

#include "Stage.h"
#include "MouseButtonUp.h"
#include <iostream>
#define TEXTURE_CONFIG_FILE "config/textures.yaml"
#define Y 0
#define H this->window.getWindowHeight()
#define TOTAL_X this->window.getWindowWidth()
#define X (TOTAL_X)/this->xPortion
#define W (TOTAL_X) - (X)
#define MATRIX_TO_PIXEL_FACTOR 100


void setSDL_Rect(struct SDL_Rect* rect, int x, int y, int w, int h) {
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

Stage::Stage(Window& window, std::string& current, int xPortion):
    window(window), textures(YAML::LoadFile(TEXTURE_CONFIG_FILE)),
    stageView(window, textures, MATRIX_TO_PIXEL_FACTOR) , current(current), xPortion(xPortion) {

    /*
    std::cerr << "\nCreande Stage: \n";
    std::cerr << "Antes del clear \n";
    window.clear();
    std::cerr << "Despues del clear \n";

    std::cerr << "Antes del render \n";
    window.render();
    std::cerr << "Despues del render\n";
*/

    this->me = (struct SDL_Rect*) malloc(sizeof(struct SDL_Rect*));
    this->setSize();
    this->camera = (struct SDL_Rect*) malloc(sizeof(struct SDL_Rect*));
    *this->camera = {0 ,0, W, H};
/*
    std::cerr << "\n\nStage creado: \n";


    std::cerr << "Antes del clear \n";
    window.clear();
    std::cerr << "Despues del clear \n";

    std::cerr << "Antes del render \n";
    window.render();
    std::cerr << "Despues del render\n\n";
    */
}

void Stage::setSize() {
    setSDL_Rect(this->me, X, Y, W, H);
}

Stage::~Stage() {
    delete(this->camera);
    delete(this->me);
}


void Stage::insert(uint32_t x, uint32_t y) {
    if (current.empty()) {
        //throw()
    }
    stageView.addTile(x,y, this->current);
}

void Stage::draw() {
    Sprite bgSprite("resources/editor-stage-bg.png", window);
    bgSprite.draw(window, this->me);
    stageView.draw(window, this->camera , X);
}

void Stage::handle(MouseButtonDown *event) {
    int xPixel = (*event).getX();
    int yPixel = (*event).getY();
    int x = (xPixel - X)/MATRIX_TO_PIXEL_FACTOR;
    int y = yPixel/MATRIX_TO_PIXEL_FACTOR;
    SDL_Point sdlPoint = {xPixel, yPixel};
    bool isIn = (bool) SDL_PointInRect(&sdlPoint, this->me);
    if (!isIn) {
        return;
    }
    try {
        current = stageView.getName(x, y);
    }
    catch (StageViewAddPositionException) {
        return;
    }
    stageView.removeTile(x,y);
    std::cerr << "New current AFTERD DOWN is: " << current<< std::endl;
}

void Stage::handle(MouseButtonUp *event) {
    int xPixel = (*event).getX();
    int yPixel = (*event).getY();
    std::cerr << "Button up in pixels " << "(" << xPixel << ", " << yPixel << ")" << std::endl;
    int x = (xPixel - X)/MATRIX_TO_PIXEL_FACTOR;
    int y = yPixel/MATRIX_TO_PIXEL_FACTOR;
    std::cerr << "Button up in matrix " << "(" << x << ", " << y << ")" << std::endl;
    SDL_Point sdlPoint = {xPixel, yPixel};
    bool isIn = (bool) SDL_PointInRect(&sdlPoint, this->me);
    if (!isIn ) {
        return;
    }
    std::cerr << "current to be add is: " << current<< std::endl;
    try {
        stageView.addTile(x, y, current);
    }
    catch (StageViewAddTileException){
        return;
    }
    current = "";
    std::cerr << "New current is: " << current<< std::endl;
}