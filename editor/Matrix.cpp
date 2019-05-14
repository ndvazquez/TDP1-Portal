//
// Created by camix on 13/05/19.
//

#include "Matrix.h"
#include <iostream>


Matrix::Matrix(int totalWidth, int totalHeight, int rectWidth, int rectHeight) {
    for (int i = 120; i < totalWidth; i += rectWidth) {
        std::vector<struct SDL_Rect*> vec;
        this->rectangles.push_back(vec);
        for (int j = 0; j < totalHeight; j += rectHeight) {
            this->insert(i, j, rectWidth, rectHeight);
        }
    }
}


Matrix::~Matrix() {
    auto it = this->rectangles.begin();
    while (it != this->rectangles.end()) {
        auto internal_it = (*it).begin();
        while (internal_it != (*it).end()) {
            delete(*internal_it);
        }
    }
}

void Matrix::insert(int x, int y, int w, int h) {
    struct SDL_Rect* rect = (struct SDL_Rect*) malloc(sizeof(struct SDL_Rect*));
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
    this->rectangles[this->rectangles.size()-1].push_back(rect);
}

SDL_Rect *Matrix::getRectangle(int x, int y) {
    struct SDL_Rect* rect = this->rectangles[x][y];
    return rect;
}
