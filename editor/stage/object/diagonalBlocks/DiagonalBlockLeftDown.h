//
// Created by camix on 17/06/19.
//

#ifndef PORTAL_DIAGONALBLOCKLEFTDOWN_H
#define PORTAL_DIAGONALBLOCKLEFTDOWN_H


#include "DiagonalBlockDown.h"

class DiagonalBlockLeftDown : public DiagonalBlockDown {
public:
    DiagonalBlockLeftDown(std::string &path, Window &window, int id, int w, int h);
    ~DiagonalBlockLeftDown();
    std::pair<float, float> MatrixPosToCenterOfMass(const std::pair<int, int> &position) override;
};


#endif //PORTAL_DIAGONALBLOCKLEFTDOWN_H
