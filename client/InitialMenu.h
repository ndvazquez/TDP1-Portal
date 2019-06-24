//
// Created by camix on 23/06/19.
//

#ifndef PORTAL_INITIALMENU_H
#define PORTAL_INITIALMENU_H


#include "../common/Window.h"
#include <vector>

#define QUIT_ACTION 0
#define CREATE_ACTION 1
#define JOIN_ACTION 2


class InitialMenu {
private:
    Window& window;
    std::vector<std::string> &gamesAvailable;

public:
    explicit InitialMenu(Window &window,
            std::vector<std::string> &gamesAvailable);

    int start();
};


#endif //PORTAL_INITIALMENU_H
