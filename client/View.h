//
// Created by ndv on 5/25/19.
//

#ifndef PORTAL_VIEW_H
#define PORTAL_VIEW_H


#include "../common/Window.h"

class View {
protected:
    Window& window;
    // Actual width and height of the view, in meters.
    float viewWidthInMeters;
    float viewHeightInMeters;
    SDL_Rect collisionBox;
    // X and Y position in pixels.
    int viewPosX;
    int viewPosY;
    // Conversion factor to transform meters to pixels.
    int mtpFactor;
public:
    View(Window& newWindow, int xPos, int yPos, int factor,
            float width, float height);
    virtual ~View() = default;
    virtual void playAnimation(SDL_Rect& camera) = 0;
    void move(float newPosX, float newPosY, int levelHeight);
    int getViewPositionX();
    int getViewPositionY();
    bool checkCollisionWithCamera(SDL_Rect& camera);
};


#endif //PORTAL_VIEW_H
