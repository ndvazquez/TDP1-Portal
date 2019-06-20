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
#include "../../../common/OutputText.h"


#define POSITIONS_ABOVE (h - 1)
#define WITHOUT_GRAVITY_SENTINEL 100
#define GRAVITY_SENTINEL 101

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


    std::pair<float, float> rectangleMatrixPosToCenterOfMass(
            const std::pair<int, int> &position,
            float w, float h);

    virtual std::pair<float, float> matrixPosToCenterOfMass(
            const std::pair<int, int> &position) = 0;



    std::pair<int, int> rectangleCenterOfMassToMatrixPos(
            const std::pair<float, float> &position, float w, float h);

    virtual std::pair<int, int> centerOfMassToMatrixPos(
            const std::pair<float, float> &pair) = 0;


    virtual bool hasCondition();
    virtual std::map<std::pair<int, int>, std::string>& getNames();

    virtual std::map<std::pair<int, int>, std::string>& getConditions();
    int getWidth();
};

#endif //PORTAL_OBJECT_H
