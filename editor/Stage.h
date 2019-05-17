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

class Stage {
private:
    Window& window;
    StageView stageView;
    std::string& current;
    struct SDL_Rect* me;
    int xPortion;
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
};


#endif //PORTAL_MATRIX_H
