//
// Created by camix on 24/06/19.
//

#include <iostream>
#include "GameNameMenu.h"
#include "../common/InputText.h"
#include "SimpleInputManager.h"

#define INVLID_GAME_REQUEST "THE GAME YOU ARE LOOKING FOR DOES NOT EXIST. ENTER ONE OF THE GAMES AVAILABLE"
#define GAME_REQUEST "ENTER GAME NAME"



GameNameMenu::GameNameMenu(Window &window,
                           std::string& gaString) :
                           window(window),
                           gaString(gaString) {
}

void GameNameMenu::getInput(InputText& input) {

}

std::string GameNameMenu::start(int rst) {
    InputText input(window, GAME_REQUEST, GREEN_MOLD);
    SimpleInputManager m;
    m.start(input, window);

    std::string gameName = input.copyText();

    while (rst == JOIN_ACTION && gaString.find(gameName) == std::string::npos) {
        InputText otherInput(window, INVLID_GAME_REQUEST, GREEN_MOLD);
        m.start(otherInput, window);
        gameName = otherInput.copyText();
    }

    return gameName;
}