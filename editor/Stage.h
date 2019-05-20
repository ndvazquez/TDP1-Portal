//
// Created by camix on 13/05/19.
//

#ifndef PORTAL_MATRIX_H
#define PORTAL_MATRIX_H

#include <vector>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include "../common/Window.h"
#include "../common/StageView.h"
#include "MouseButtonDown.h"
#include "MouseButtonUp.h"

class Stage {
private:
    Window& window;
    YAML::Node textures;
    StageView stageView;
    std::string& current;
    int xPortion;
    struct SDL_Rect* me;
    struct SDL_Rect* camera;
    //map<map<char, int>, uint8_t> matrix;
    //uint8_t& current;
    //for now is hard

public:
    explicit Stage(Window& window, std::string& current, int xPortion);

    //Stage(uint8_t& current)//, uint32_t xStart);
    ~Stage();
    void setSize();
    // (x,y) pixeles.
    void insert(uint32_t x, uint32_t y);
    void draw();

    void handle(MouseButtonDown *event);

    void handle(MouseButtonUp *event);
};


#endif //PORTAL_MATRIX_H
