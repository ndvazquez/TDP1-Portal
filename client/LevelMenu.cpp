//
// Created by camix on 24/06/19.
//

#include <iostream>
#include "LevelMenu.h"
#include "../common/OutputText.h"
#include "../common/InputText.h"


#define ENTERING_DONE "(DONE)"
#define OPTIONS_TITLE "LIST OF LEVEL AVAILABLES"

#define EXTENSION ".yaml"

LevelMenu::LevelMenu(Window &window,
                         std::vector<std::string> &levelsAvailable) :
        window(window), levelsAvailable(levelsAvailable) {
}

std::string LevelMenu::start(const char* principalMessage) {
    OutputText listTitle(window, OPTIONS_TITLE, LIGHT_GRAY);
    std::vector<OutputText*> optionsList;
    for (auto & it : levelsAvailable) {
        int len = it.size();
        optionsList.push_back(new OutputText(window, it.substr(0,len-5).c_str(), LIGHT_GRAY));
    }



    InputText input(window, principalMessage, GREEN_MOLD);


    SDL_Event e;
    bool close = false;
    int width = window.getWindowWidth();
    int height = window.getWindowHeight();

    // Setting done option
    OutputText doneImage(window, ENTERING_DONE, WHITE);
    int imageW = doneImage.getWidth();
    SDL_Rect done = {width - imageW - 20,height - 30,50,50};

    std::string& enteredLevel = input.getText();
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) { // check to see if an event has happened
            if ((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                enteredLevel = "";
                quit = true;
                break;
            }
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
                int x = 20;
                int y = 20;
                listTitle.draw(x,y);
                y += 40;
                for (auto it : optionsList) {
                    it->draw(x, y);
                    y += it->getHeight() + 20;
                }
                doneImage.draw(&done);
                input.drawFromTheCenter(0, 0);
                window.render();
            }
        }
    }

    if(close) {
        throw CloseException();
    }

    auto it = optionsList.begin();
    while (it != optionsList.end()) {
        auto act = *it;
        it++;
        delete act;
    }

    std::cerr << "\nENTERED LEVEL:" << enteredLevel << "\n" << std::endl;
    return enteredLevel + EXTENSION;
}
