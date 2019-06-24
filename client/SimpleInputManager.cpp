//
// Created by camix on 24/06/19.
//

#include "SimpleInputManager.h"

#define DONE_MESSAGE "(DONE)"

SimpleInputManager::SimpleInputManager() = default;

SimpleInputManager::~SimpleInputManager() = default;

void SimpleInputManager::start(InputText &input,
                               Window &window,
                               const char* secondOutput,
                               const char* thirdOutput) {
    SDL_Event e;
    bool close = false;
    int width = window.getWindowWidth();
    int height = window.getWindowHeight();

    // Setting done option
    OutputText doneImage(window, DONE_MESSAGE, WHITE);
    int imageW = doneImage.getWidth();
    SDL_Rect done = {width - imageW - 40,height - 40,50,50};


    OutputText sOImage(window, secondOutput, GREEN_MOLD);
    int sOW = sOImage.getWidth();
    OutputText tOImage(window, thirdOutput, GREEN_MOLD);
    int tOW = tOImage.getWidth();


    bool quit = false;
    while (!quit) {
        SDL_Delay(1);
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
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                quit = true;
                break;
            } else {
                input.handle(&e);
                window.clear();
                window.drawBlackBackground();
                sOImage.drawFromTheCenter(0, -50);
                tOImage.drawFromTheCenter(0, -80);
                doneImage.draw(&done);
                input.drawFromTheCenter(0, 0);
                window.render();
            }
        }
    }

    if (close) {
        throw CloseException();
    }
}
