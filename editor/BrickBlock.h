//
// Created by camix on 13/05/19.
//

#ifndef PORTAL_BRICKBLOCK_H
#define PORTAL_BRICKBLOCK_H
#include <SDL.h>
#include <SDL_image.h>
#include "../common/Window.h"
#include "../common/Sprite.h"


class BrickBlock {
private:
    Window& window;
    Sprite sprite;
public:
    BrickBlock(Window& window);
    ~BrickBlock();
    void draw(int x, int y);
    void draw(SDL_Rect* rect);
};


#endif //PORTAL_BRICKBLOCK_H
