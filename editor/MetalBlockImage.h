//
// Created by camix on 13/05/19.
//

#ifndef PORTAL_METALBLOCKIMAGE_H
#define PORTAL_METALBLOCKIMAGE_H

#include <SDL.h>
#include <SDL_image.h>
#include "../common/Window.h"
#include "../common/Sprite.h"


class MetalBlockImage {
private:
    Window& window;
    Sprite sprite;
public:
    explicit MetalBlockImage(Window& window);
    ~MetalBlockImage();
    void draw(int x, int y);
    void draw(SDL_Rect* rect);
};


#endif //PORTAL_METALBLOCKIMAGE_H
