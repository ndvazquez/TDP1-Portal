//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_ROCK_H
#define PORTAL_ROCK_H


#include "../../../common/Window.h"
#include "StaticObject.h"

class Rock : public StaticObject {
public:
    Rock(std::string &path, Window &window, int id, int w, int h);
    ~Rock();

    std::pair<float, float> MatrixPosToCenterOfMass(const std::pair<int, int> &position) override;
};


#endif //PORTAL_ROCK_H
