//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_OBJECT_H
#define PORTAL_OBJECT_H

#include <vector>
#include <unordered_map>
#include <map>
#include <sstream>
#include "../../../common/Sprite.h"
#include "ObjectException.h"

#define POSITIONS_ABOVE (h - 1)
#define SENTINEL ""
#define BLOCK_SENTINEL "KindOfARock"

class Object {
protected:
    std::vector<std::string> floors;
    int w;
    int h;

public:
    Object(std::string name, int w, int h);

    virtual void hasToBeOn(const std::string &name);

    virtual void draw(SDL_Rect *rect) = 0;

    virtual void addTo(int x, int y, std::map<std::pair<int, int>,
            std::string> &tiles, std::string sentinel = SENTINEL);

    virtual void setName(std::pair<int, int>& position, std::string &enteredName);

    void addWithGravityTo(int x, int y, std::map<std::pair<int, int>, std::string> &tiles);

    virtual void removeFrom(int x, int y, std::map<std::pair<int, int>, std::string> &tiles,
                            std::unordered_map<std::string, Object *> &textures);

    virtual bool hasGravity();
    virtual void addCondition(std::pair<int, int> position, std::string& condition);

    virtual bool doesThisNameExist(std::string &string);

    virtual bool hasCondition();

    std::string name;

    std::string getMetersPosition(const std::pair<int, int> position);
};

#endif //PORTAL_OBJECT_H
