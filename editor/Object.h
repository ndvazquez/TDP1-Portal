//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_OBJECT_H
#define PORTAL_OBJECT_H

#include <vector>
#include "../common/Sprite.h"

class Object {
protected:
    std::vector<std::string> floors;

public:
    virtual void hasToBeOn(const std::string& name);
    virtual void draw(SDL_Rect* rect) = 0;
    virtual bool canBeOn(const std::string& name);
    virtual bool canBeOn() = 0;
};


#endif //PORTAL_OBJECT_H
