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
#define WITHOUT_GRAVITY_SENTINEL "WithoutGravitySentinel"
#define GRAVITY_SENTINEL "GravitySentinel"

class Object {
protected:
    std::vector<std::string> floors;
    int w;
    int h;
    std::string name;

public:
    Object(std::string name, int w, int h);

    virtual void hasToBeOn(const std::string &name);

    virtual void draw(SDL_Rect *rect) = 0;

    virtual void addTo(int x, int y, std::map<std::pair<int, int>,
            std::string> &tiles, std::unordered_map<std::string,
            Object *>& texturesL, bool needGravitySentinel = false);

    virtual void setName(std::pair<int, int>& position, std::string &enteredName);

    void addWithGravityTo(int x, int y, std::map<std::pair<int, int>,std::string>
    &tiles,
                          std::unordered_map<std::string, Object *>& textures);

    virtual void removeFrom(int x, int y, std::map<std::pair<int, int>, std::string> &tiles,
                            std::unordered_map<std::string, Object *> &textures);

    virtual bool hasGravity();
    virtual void addCondition(std::pair<int, int> position, std::string& condition);

    virtual bool doesThisNameExist(std::string &string);


    std::string getMetersPosition(const std::pair<int, int> position);

    virtual bool hasCondition();
};

#endif //PORTAL_OBJECT_H
