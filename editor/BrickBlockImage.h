//
// Created by camix on 13/05/19.
//

#ifndef PORTAL_BRICKBLOCKIMAGE_H
#define PORTAL_BRICKBLOCKIMAGE_H
#include <SDL.h>
#include <SDL_image.h>
#include "../common/Window.h"
#include "../common/Sprite.h"


class BrickBlockImage {
private:
    Window& window;
    Sprite sprite;
public:
    explicit BrickBlockImage(Window& window);
    ~BrickBlockImage();
    void draw(int x, int y);
    void draw(SDL_Rect* rect);
};


#endif //PORTAL_BRICKBLOCKIMAGE_H
