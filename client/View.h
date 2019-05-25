//
// Created by ndv on 5/25/19.
//

#ifndef PORTAL_VIEW_H
#define PORTAL_VIEW_H


#include "../common/Window.h"

class View {
protected:
    Window& window;
    int viewWidth;
    int viewHeight;
    int viewPosX;
    int viewPosY;
    int mtpFactor;
public:
    View(Window& newWindow, int xPos, int yPos, int factor);
    virtual ~View() = default;
    virtual void playAnimation() = 0;
    void move(float newPosX, float newPosY, int levelHeight);
};


#endif //PORTAL_VIEW_H
