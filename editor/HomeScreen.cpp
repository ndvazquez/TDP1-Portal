//
// Created by camix on 20/06/19.
//

#include <iostream>
#include "HomeScreen.h"
#include "../common/Window.h"

#define SET_YAML_WRONG_MESSAGE "IF YOU REALLY DONT WANT TO DIE"
#define SET_YAML_MESSAGE "IF YOU REALLY WANT THE CAKE, ENTER THE NAME OF A STGE"
#define NO_YAML "(SKIP)"
#define ENTERING_DONE "(OK, HERE IS THE NAME. CAN I ALREADY HAVE MY CAKE?)"

#define AFTER_ENTER_FILE "HAHAHA YOU WISH.... IT WON'T BE THAT EASY"
#define AFTER_SKIP "IF YOU THINK YOU ARE NOT WORTHY OF THE CAKE MAYBE YOU SHOULD NOT BE HERE"


#define AFTER_QUIT1 "IT SEEMS THAT U WANT TO ESCAPE"
#define AFTER_QUI2 "WE WILL KEEP WATCHING U..."


HomeScreen::HomeScreen(Window &window) :
        input(window, SET_YAML_MESSAGE, GREEN_MOLD) ,
        window(window) ,
        yamlPath(input.getText()) {}

HomeScreen::~HomeScreen() = default;

std::string & HomeScreen::start(bool withAnswer) {
    input.resetText();
    SDL_Event e;
    bool close = false;
    int width = window.getWindowWidth();
    int height = window.getWindowHeight();

    // Setting skip option
    OutputText skipImage(window, NO_YAML, WHITE);
    SDL_Rect skip = {50,height - 100,50,50};
    // Setting done option
    OutputText doneImage(window, ENTERING_DONE, WHITE);
    int imageW = doneImage.getWidth();
    SDL_Rect done = {width - imageW - 50,height - 100,50,50};


    std::string answer;
    const char* droppedFilePath;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) { // check to see if an event has happened
            if (e.type == SDL_MOUSEBUTTONDOWN &&
                e.button.clicks == 1 &&
                e.button.button == SDL_BUTTON_LEFT) {
                SDL_Point sdlPoint = {e.button.x, e.button.y};
                if ((bool) SDL_PointInRect(&sdlPoint, &skip)) {
                    answer = AFTER_SKIP;
                    yamlPath = "";
                    quit = true;
                    break;
                }
                if ((bool) SDL_PointInRect(&sdlPoint, &done)) {
                    answer = AFTER_ENTER_FILE;
                    quit = true;
                    break;
                }
            }
            if (e.type == SDL_QUIT) {
                answer = AFTER_QUIT1;
                quit = true;
                close = true;
                break;
            }
            if (e.type == SDL_DROPFILE) {
                answer = AFTER_ENTER_FILE;
                yamlPath = e.drop.file;
                quit = true;
                break;
            }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                answer = AFTER_ENTER_FILE;
                quit = true;
                break;
            } else {
                input.handle(&e);
                window.clear();
                window.drawBlackBackground();
                skipImage.draw(&skip);
                doneImage.draw(&done);
                input.drawFromTheCenter(0, 0);
                window.render();
            }
        }
    }
    if (withAnswer) {
        doneImage.writeTheScreen(answer);
    }
    if (close) {
        answer = AFTER_QUI2;
        if (withAnswer) {
            doneImage.writeTheScreen(answer);
        }
        throw CloseException();
    }
    return yamlPath;
}
