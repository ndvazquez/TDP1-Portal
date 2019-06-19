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

    /* Returns the x component of a Coordinate */
    float getX();

    /* Returns the y component of a Coordinate */
    float getY();
};

#endif //PORTAL_COORDINATE_H
