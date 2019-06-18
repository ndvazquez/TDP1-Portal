//
// Created by camix on 28/05/19.
//

#ifndef PORTAL_CAKE_H
#define PORTAL_CAKE_H

#include "AnimatedObject.h"

class Cake : public AnimatedObject {
public:
    Cake(std::string &path, Window &window, int totalFrames, int id, int w, int h);
    ~Cake();

    std::pair<float, float> MatrixPosToCenterOfMass(const std::pair<int, int> &position) override;
};


#endif //PORTAL_CAKE_H
