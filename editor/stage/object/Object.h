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
#include "../../../common/constants.h"

#define POSITIONS_ABOVE (h - 1)
#define WITHOUT_GRAVITY_SENTINEL 23
#define GRAVITY_SENTINEL 24

class Object {
protected:
    int w;
    int h;
    int name;

public:
    Object(int id, int w, int h);

    virtual void draw(SDL_Rect *rect) = 0;

    virtual void addTo(int x, int y,
                       std::map<std::pair<int, int>, int> &tiles,
                       std::unordered_map<int, Object *> &texturesL,
                       bool needGravitySentinel = false);

    virtual void setName(std::pair<int, int>& position,
                    std::string &enteredName);

    void addWithGravityTo(int x, int y,
                          std::map<std::pair<int, int>, int> &tiles,
                          std::unordered_map<int, Object *> &textures);

    virtual void removeFrom(int x, int y,
                            std::map<std::pair<int, int>, int> &tiles,
                            std::unordered_map<int, Object *> &textures);

    virtual bool hasGravity();
    virtual void addCondition(std::pair<int, int> position,
                    std::string& condition);

    virtual bool doesThisNameExist(std::string &string);


    virtual std::pair<float, float> rectangleCenterOfMass(
                     const std::pair<int, int> &position,
                     float w, float h);
    virtual std::pair<float, float> triangleCenterOfMass(
                    const std::pair<float, float> &a,
                    const std::pair<float, float> &b,
                    const std::pair<float, float> &c);

    virtual std::pair<float, float> MatrixPosToCenterOfMass(
            const std::pair<int, int> &position) = 0;

    virtual std::pair<int, int> rectangleCenterOfMassToMatrixPos(
            const std::pair<float, float> &position);

    virtual bool hasCondition();
    virtual std::map<std::pair<int, int>, std::string>& getNames();
    int getWidth();

    // virtual std::pair<int, int> centerOfMassToMatrixPos(std::pair<float, float> &pair) = 0;
};

#endif //PORTAL_OBJECT_H
