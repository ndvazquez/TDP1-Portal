//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_STATICOBJECT_H
#define PORTAL_STATICOBJECT_H


#include "../common/Sprite.h"
#include "Object.h"

class StaticObject : public Object {
protected:
    Window& window;
    Sprite sprite;

public:
    StaticObject(const std::string& path, Window& window);
    ~StaticObject();
    void draw(SDL_Rect* rect) override;

    bool canBeOn() = 0;
};


#endif //PORTAL_STATICOBJECT_H
