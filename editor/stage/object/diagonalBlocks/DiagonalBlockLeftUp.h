//
// Created by camix on 17/06/19.
//

#ifndef PORTAL_DIAGONALBLOCKLEFTUP_H
#define PORTAL_DIAGONALBLOCKLEFTUP_H


#include "DiagonalBlockUp.h"

class DiagonalBlockLeftUp : public DiagonalBlockUp {
public:
    DiagonalBlockLeftUp(std::string &path, Window &window, int id, int w, int h);
    ~DiagonalBlockLeftUp();
    std::pair<float, float> MatrixPosToCenterOfMass(const std::pair<int, int> &position) override;
};


#endif //PORTAL_DIAGONALBLOCKLEFTUP_H
