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
#include "MouseButton.h"
#include "StageController.h"

class Stage {
private:
    Window& window;
    YAML::Node textures;
    StageController controller;
    std::string& current;
    int xPortion;
    struct SDL_Rect* me;
    struct SDL_Rect* camera;
    std::map<std::string, bool> gravity;
    //uint8_t& current;
    //for now is hard

public:
    explicit Stage(Window& window, std::string& current, int xPortion);

    //Stage(uint8_t& current)//, uint32_t xStart);
    ~Stage();
    void setSize();
    // (x,y) pixeles.
    void draw();
    void handleMouseButtonDown(MouseButton& event);

    void handleMouseButtonUp(MouseButton& event);

    void handleMouseDoubleCick(MouseButton& event);
};


#endif //PORTAL_MATRIX_H
