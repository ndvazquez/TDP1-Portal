//
// Created by camix on 20/06/19.
//

#ifndef PORTAL_HOMESCREEN_H
#define PORTAL_HOMESCREEN_H


#define CLOSED_EXC "The user want to close the process\n"

#include "../common/Window.h"
#include "../common/InputText.h"

class HomeScreen {
    InputText input;
    Window &window;
    std::string& yamlPath;

public:
    HomeScreen(Window &window);
    ~HomeScreen();
    std::string &start(bool withAnswer = false);
};

class CloseException: public std::exception {
public:
    CloseException() = default;
    virtual const char* what() const throw() {
        return CLOSED_EXC;
    }
};

#endif //PORTAL_HOMESCREEN_H
