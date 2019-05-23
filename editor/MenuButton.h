//
// Created by camix on 18/05/19.
//

#ifndef PORTAL_MENUBUTTON_H
#define PORTAL_MENUBUTTON_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "../common/Window.h"

class MenuButton {
protected:
    struct SDL_Rect* myPosition;
    std::string name;
    std::string path;

public:
    MenuButton(struct SDL_Rect* rect, std::string name, std::string& path);
    ~MenuButton();
    MenuButton& operator=(MenuButton origin);
    MenuButton(const MenuButton& origin);
    bool has(Sint32 x, Sint32 y);
    std::string getName();
    void draw(Window& window);

    void set(SDL_Rect *rect);

    int setRectangle(int x, int y, int w, int h);
};


#endif //PORTAL_MENUBUTTON_H
