//
// Created by camix on 21/06/19.
//

#include "InputManager.h"

#define ENTERING_NAME_DONE "OK"

InputManager::InputManager(Window &window, const char *message, SDL_Rect *rect) :
    input(window, message, GREEN_MOLD) ,
    window(window),
    rect(rect) {
}

std::string & InputManager::startReading(std::pair<int, int> &position,
                                         Object *obj,
                                         SDL_Rect *camera,
                                         int stageY,
                                         View stageView) {
    SDL_Event e;
    bool close = false;
    int x = rect->x;
    int w = rect->w;
    int height = rect->h;
    int y = rect->y;
    std::string& yamlPath = input.getText();

    // Setting done option
    OutputText doneImage(window, ENTERING_NAME_DONE, WHITE);
    int imageW = doneImage.getWidth();
    SDL_Rect done = {w - 50, y + height - 50,0,0};

    SDL_Rect inputPos = {x + w/2, y, 0, 0};
    //std::string answer;
    const char* droppedFilePath;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) { // check to see if an event has happened
            if (e.type == SDL_MOUSEBUTTONDOWN &&
                e.button.clicks == 1 &&
                e.button.button == SDL_BUTTON_LEFT) {
                SDL_Point sdlPoint = {e.button.x, e.button.y};
                if ((bool) SDL_PointInRect(&sdlPoint, &done)) {
                    quit = true;
                    break;
                }
            }
            if (e.type == SDL_QUIT) {
                quit = true;
                close = true;
                break;
            }
            if (e.type == SDL_DROPFILE) {
                yamlPath = e.drop.file;
                quit = true;
                break;
            }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                quit = true;
                break;
            } else {
                input.handle(&e);
                window.clear();
                window.drawBlackBackground();
                stageView.drawObject(obj, position, camera, stageY);
                doneImage.draw(&done);
                input.draw(&inputPos);
                window.render();
            }
        }
    }
    if (close) {
        throw CloseInputManagerException();
    }
    return yamlPath;
}

InputManager::~InputManager() = default;