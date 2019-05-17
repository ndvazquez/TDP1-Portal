//
// Created by camix on 13/05/19.
//

#ifndef PORTAL_MATRIX_H
#define PORTAL_MATRIX_H

#include <vector>
#include <map>
#include <SDL.h>
#include <SDL_image.h>

class Stage {
private:
    map<map<char, int>, uint8_t> matrix;
    uint8_t& current;
    //for now is hard
    uint32_t xStart;

public:
    Stage(uint8_t& current, uint32_t xStart);
    ~Stage();
    // (x,y) pixeles.
    void insert(Pixel position);
    void draw();
};


#endif //PORTAL_MATRIX_H
