//
// Created by camix on 21/06/19.
//

#ifndef PORTAL_INPUTMANAGER_H
#define PORTAL_INPUTMANAGER_H


#include "../../../common/Window.h"
#include "../../../common/InputText.h"
#include "../View.h"

class InputManager {
private:
    InputText input;
    Window &window;
    SDL_Rect* rect;

public:
    InputManager(Window &window, const char *message, SDL_Rect *rect);
    ~InputManager();
    std::string &enteredString(std::pair<int, int> &position,
                               Object* obj,
                               SDL_Rect *camera,
                               int stageY,
                               View stageView);
};

class CloseInputManagerException: public std::exception {
public:
    CloseInputManagerException() = default;
    virtual const char* what() const throw() {
        return "CloseInputManagerException";
    }
};

#endif //PORTAL_INPUTMANAGER_H
