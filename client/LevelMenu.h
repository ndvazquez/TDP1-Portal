//
// Created by camix on 24/06/19.
//

#ifndef PORTAL_LEVELMENU_H
#define PORTAL_LEVELMENU_H



#include "../common/Window.h"

#include "CloseException.h"
#include <vector>

class LevelMenu {
private:
    Window& window;
    std::vector<std::string>& levelsAvailable;

public:
    LevelMenu(Window& window, std::vector<std::string>& levelsAvailable);

    std::string start(const char *principalMessage);
};


#endif //PORTAL_LEVELMENU_H
