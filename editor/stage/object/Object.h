//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_OBJECT_H
#define PORTAL_OBJECT_H

#include <vector>
#include <unordered_map>
#include <map>
#include "../../../common/Sprite.h"
#include "ObjectException.h"


class Object {
protected:
    std::vector<std::string> floors;
    std::string name;
    int w;
    int h;

public:
    Object(std::string  name, int w, int h);
    virtual void hasToBeOn(const std::string& name);
    virtual void draw(SDL_Rect* rect) = 0;

    virtual void addTo(int x, int y, std::map<std::pair<int, int>,
            std::string> &tiles);
    virtual void setName();

    void addWithGravityTo(int x, int y, std::map<std::pair<int, int>, std::string> &tiles);

    virtual void removeFrom(int x, int y, std::map<std::pair<int, int>, std::string> &tiles,
                            std::unordered_map<std::string, Object *>& textures);

    virtual bool hasGravity();
};

#endif //PORTAL_OBJECT_H
