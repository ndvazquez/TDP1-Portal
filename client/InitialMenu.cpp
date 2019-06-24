//
// Created by camix on 23/06/19.
//

#include <boost/fusion/container/vector.hpp>
#include <iostream>
#include "InitialMenu.h"
#include "../common/OutputText.h"
#include "../common/InputText.h"

#define PINCIPAL_MESSAGE  "DO YOU WANT TO (CREATE) OR (JOIN) A GAME?"
#define CREATE_MESSAGE "(CREATE)"
#define JOIN_MESSAGE "(JOIN)"
#define SENTINEL_MESSAGE "  "
#define NO_GAMES_AVAILABLE "NO GAMES AVALIABLE AT THE MOMENT, (CREATE) ONE!"
#define GAMES_AVAILABLE "LIST OF GAMES AVALIABLE:"

InitialMenu::InitialMenu(Window &window,
                    std::vector<std::string> &gamesAvailable) :
        window(window),
        gamesAvailable(gamesAvailable) {}

int InitialMenu::start() {
    SDL_Event e;

    int width = window.getWindowWidth();
    int height = window.getWindowHeight();

    OutputText principal(window, PINCIPAL_MESSAGE, GREEN_MOLD);
    int principalImageH = principal.getHeight();

    // Setting skip option
    OutputText createImage(window, CREATE_MESSAGE, WHITE);
    int createImageW = createImage.getWidth();
    int createImageH = createImage.getHeight();
    int createXCenter = width/2 - createImageW/2;
    int createYCenter = height/2 - createImageH/2;
    SDL_Rect create = {createXCenter, createYCenter + principalImageH,50,50};

    // Setting done option
    OutputText joinImage(window, JOIN_MESSAGE, WHITE);
    int joinImageW = joinImage.getWidth();
    int joinImageH = joinImage.getHeight();
    int joinXCenter = width/2 - joinImageW/2;
    int joinYCenter = createYCenter + createImageH + joinImageH;
    SDL_Rect join = {joinXCenter, joinYCenter, 50, 50};


    bool thereAreGamesAvailable = !gamesAvailable.empty();
    OutputText available(window, SENTINEL_MESSAGE, LIGHT_GRAY);
    OutputText noAvailable(window, SENTINEL_MESSAGE, LIGHT_GRAY);
    std::vector<OutputText*> optionsList;

    if (!thereAreGamesAvailable) {
        available.changeMessage(NO_GAMES_AVAILABLE);
    } else {
        noAvailable.changeMessage(GAMES_AVAILABLE);
        for (auto & it : gamesAvailable) {
            optionsList.push_back(new OutputText(window, it.c_str(), LIGHT_GRAY));
        }
    }

    int ret;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) { // check to see if an event has happened
            if (e.type == SDL_MOUSEBUTTONDOWN &&
                e.button.clicks == 1 &&
                e.button.button == SDL_BUTTON_LEFT) {
                SDL_Point sdlPoint = {e.button.x, e.button.y};
                if ((bool) SDL_PointInRect(&sdlPoint, &create)) {
                    ret = CREATE_ACTION;
                    quit = true;
                    break;
                }
                if ((bool) SDL_PointInRect(&sdlPoint, &join) &&
                        thereAreGamesAvailable) {
                    ret = JOIN_ACTION;
                    quit = true;
                    break;
                }
            }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN){
                ret = CREATE_ACTION;
                quit = true;
                break;
            }
            if (e.type == SDL_QUIT) {
                ret = QUIT_ACTION;
                quit = true;
                break;
            } else {
                window.clear();
                window.drawBlackBackground();
                createImage.draw(&create);
                if (thereAreGamesAvailable) {
                    joinImage.draw(&join);
                }
                principal.drawFromTheCenter(0, 0);
                int x = 20;
                int y = 20;
                available.draw(x, y);
                noAvailable.draw(x, y);
                y += 10;
                for (auto it : optionsList) {
                    it->draw(x, y);
                    y += it->getHeight() + 20;
                }
                window.render();
            }
        }
    }
    /*
    auto it = optionsList.begin();
    while (it != optionsList.end()) {
        auto act = *it;
        it++;
        delete act;
    }*/

    return ret;
}