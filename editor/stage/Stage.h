//
// Created by camix on 13/05/19.
//

#ifndef PORTAL_MATRIX_H
#define PORTAL_MATRIX_H

#define NOT_INSIDE_ME "The event was't on the stage"

#include <vector>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include "../../common/Window.h"
#include "../MouseButton.h"
#include "Controller.h"

class Stage {
private:
    Window& window;
    YAML::Node textures;
    Controller controller;
    int* current;
    int yPortion;
    struct SDL_Rect me;
    struct SDL_Rect camera;
    std::map<std::string, bool> gravity;
    //uint8_t& current;
    //for now is hard

public:
    explicit Stage(Window &window, int *current, int yPortion, std::string &yamlPath);

    //Stage(uint8_t& current)//, uint32_t xStart);
    ~Stage();
    // (x,y) pixeles.
    void draw(int x, int y);
    void handleMouseButtonDown(MouseButton& event);

    void handleMouseButtonUp(MouseButton& event);

    void handleMouseDoubleClick(MouseButton &event);
    void handleMouseRightClick(MouseButton &event);

    void save();

    void pixelToMatrix(MouseButton &event, int *xPixel, int *yPixel, int *x, int *y);

    void handleLeft();

    void handleRight();

    void handleUp();

    void handleDown();
};


class StageNotInsideMeException : public std::exception {
public:
    const char* what() const noexcept override {
        return NOT_INSIDE_ME;
    }
};

#endif //PORTAL_MATRIX_H
