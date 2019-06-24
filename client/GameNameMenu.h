//
// Created by camix on 24/06/19.
//

#ifndef PORTAL_GAMENAMEMENU_H
#define PORTAL_GAMENAMEMENU_H

#include "../common/Window.h"
#include "../common/constants.h"
#include "../common/InputText.h"

class GameNameMenu {
private:
    Window& window;
    std::string& gaString;

public:
    explicit GameNameMenu(Window& window,
                          std::string& gaString);

    std::string start(int rst);

    void getInput(InputText &input);
};


#endif //PORTAL_GAMENAMEMENU_H
