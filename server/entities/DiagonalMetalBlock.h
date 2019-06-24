//
// Created by cecix on 13/05/19.
//

#ifndef PORTAL_DIAGONALMETALBLOCK_H
#define PORTAL_DIAGONALMETALBLOCK_H

#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"
#include "stage-support/Coordinate.h"

class DiagonalMetalBlock: public Entity  {
private:
    bool portal;
    float angle;
    float x_diagonal_center_mass;
    float y_diagonal_center_mass;
    void calculateCenterMass();

public:
    explicit DiagonalMetalBlock(b2Body* body, float angle);
    
    /* Returns the x coordinate of the CM if it were a square */
    float getXCM();

    /* Returns the y coordinate of the CM if it were a square */
    float getYCM();

    /* Handles collision against other objects in the world */
    void handleCollision(Entity* entity) override;

    /* Returns the velocity that has to be applied to any
     * object colliding against a DiagonalMetalBlock to bounce */
    b2Vec2 calculateVelocity();
};

#endif //PORTAL_DIAGONALMETALBLOCK_H
