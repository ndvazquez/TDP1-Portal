//
// Created by camix on 21/05/19.
//

#ifndef PORTAL_STAGEVIEW_H
#define PORTAL_STAGEVIEW_H

#include <unordered_map>
#include <map>

#include "../common/Window.h"
#include "../common/Sprite.h"

class StageView {
private:
    Window& window;
    int factor;
    std::unordered_map<std::string, Sprite*>& textures;
    std::map<std::pair<int, int>, std::string>& tiles;

public:
    StageView(Window& window, int factor, std::unordered_map<std::string, Sprite*>& textures, std::map<std::pair<int, int>, std::string>& tiles);
    ~StageView();
    void draw(SDL_Rect *camera, int xStart);
};


#endif //PORTAL_STAGEVIEW_H
