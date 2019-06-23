//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_BLOCK_H
#define PORTAL_BLOCK_H


#include "StaticObject.h"


class Block : public StaticObject {
public:
    Block(std::string &path, Window &window, int id, int w, int h);
    ~Block();

    //void removeFrom(int x, int y, std::map<std::pair<int, int>, std::string> &tiles,
    //                std::unordered_map<std::string, Object *>& map) override;

    bool hasGravity() override;
    std::pair<float, float> matrixPosToCenterOfMass(
            const std::pair<int, int> &position) override;
    std::pair<int, int> centerOfMassToMatrixPos(
            const std::pair<float, float> &pair) override;
};


#endif //PORTAL_BLOCK_H
