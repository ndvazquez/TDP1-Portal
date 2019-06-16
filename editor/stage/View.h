//
// Created by camix on 21/05/19.
//

#ifndef PORTAL_VIEW_H
#define PORTAL_VIEW_H

#include <unordered_map>
#include <map>

#include "../../common/Window.h"
#include "../../common/Sprite.h"
#include "object/Object.h"

class View {
private:
    Window& window;
    int factor;
    std::unordered_map<std::string, Object*>& textures;
    std::map<std::pair<int, int>, std::string>& tiles;

public:
    View(Window& window, int factor, std::unordered_map<std::string, Object*>& textures, std::map<std::pair<int, int>, std::string>& tiles);
    ~View();
    void draw(SDL_Rect *camera, int xStart);
    int getWindowHeight();
};


#endif //PORTAL_VIEW_H
