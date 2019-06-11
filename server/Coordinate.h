//
// Created by cecix on 13/05/19.
//

#ifndef PORTAL_COORDINATE_H
#define PORTAL_COORDINATE_H


class Coordinate {
private:
    float x_pos;
    float y_pos;

public:
    Coordinate(float x_pos, float y_pos);
    bool operator==(const Coordinate&);
    bool operator!=(const Coordinate&);
    float getX();
    float getY();
};


#endif //PORTAL_COORDINATE_H
