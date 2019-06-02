//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_ANIMATEDOBJECT_H
#define PORTAL_ANIMATEDOBJECT_H


#include "../../common/AnimatedSprite.h"
#include "Object.h"

class AnimatedObject : public Object {
protected:
    Window& window;
    AnimatedSprite sprite;

public:
    AnimatedObject(std::string& path, Window& window, int totalFrames, const std::string& name, int w, int h);
    void draw(SDL_Rect* rect) override;
    ~AnimatedObject();
};


#endif //PORTAL_ANIMATEDOBJECT_H
