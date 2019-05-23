//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_ANIMATEDOBJECT_H
#define PORTAL_ANIMATEDOBJECT_H


#include "../common/AnimatedSprite.h"
#include "Object.h"

class AnimatedObject : public Object {
protected:
    Window& window;
    AnimatedSprite sprite;

public:
    AnimatedObject(const std::string& path, Window& window, int totalFrames, const std::string& name);
    void draw(SDL_Rect* rect) override;
    ~AnimatedObject();

    bool canBeOn() override = 0;
};


#endif //PORTAL_ANIMATEDOBJECT_H
