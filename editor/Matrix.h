//
// Created by camix on 13/05/19.
//

#ifndef PORTAL_MATRIX_H
#define PORTAL_MATRIX_H

#include <vector>
#include <map>
#include <SDL.h>
#include <SDL_image.h>

class Matrix {
private:
    std::vector<std::vector<struct SDL_Rect*>> rectangles;

public:
    Matrix(int totalWidth, int totalHeight, int rectWidth, int rectHeight);
    ~Matrix();
    void insert(int x, int y, int w, int h);

    SDL_Rect *getRectangle(int x, int y);
};


#endif //PORTAL_MATRIX_H
