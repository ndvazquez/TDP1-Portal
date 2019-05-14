//
// Created by camix on 13/05/19.
//

#ifndef PORTAL_BRICKBLOCKCONTAINER_H
#define PORTAL_BRICKBLOCKCONTAINER_H
#include <vector>
#include <map>
#include "BrickBlockImage.h"
#include <SDL.h>
#include <SDL_image.h>

class BrickBlockContainer {
private:
    std::vector<SDL_Rect*> BrickBlocks;

public:
    BrickBlockContainer();
    ~BrickBlockContainer();
    void insert(SDL_Rect* rect);

    void draw(Window& window);
};


#endif //PORTAL_BRICKBLOCKCONTAINER_H
