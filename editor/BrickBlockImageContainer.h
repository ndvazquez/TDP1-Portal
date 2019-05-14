//
// Created by camix on 13/05/19.
//

#ifndef PORTAL_BRICKBLOCKIMAGECONTAINER_H
#define PORTAL_BRICKBLOCKIMAGECONTAINER_H
#include <vector>
#include <map>
#include "BrickBlockImage.h"
#include <SDL.h>
#include <SDL_image.h>

class BrickBlockImageContainer {
private:
    std::vector<SDL_Rect*> BrickBlocks;

public:
    BrickBlockImageContainer();
    ~BrickBlockImageContainer();
    void insert(SDL_Rect* rect);

    void draw(Window& window);
};


#endif //PORTAL_BRICKBLOCKIMAGECONTAINER_H
