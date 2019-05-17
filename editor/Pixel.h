//
// Created by camix on 15/05/19.
//

#ifndef TDP1_PORTAL_PIXEL_H
#define TDP1_PORTAL_PIXEL_H


#include <stdint-gcc.h>

class Pixel {
private:
    uint32_t x;
    uint32_t y;

public:
    Pixel(uint32_t x, uint32_t y);
    ~Pixel();
    void toMatrixPosition(uint32_t start_x, uint32_t end_y,\
                            uint32_t& matrix_x, uint32_t& matrix_y,\
                            uint32_t size);
};


#endif //TDP1_PORTAL_PIXEL_H
