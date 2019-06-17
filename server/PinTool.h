//
// Created by cecix on 17/06/19.
//

#ifndef PORTAL_PINTOOL_H
#define PORTAL_PINTOOL_H


#include <chrono>
#include "Entity.h"

class PinTool: public Entity {
private:
    std::chrono::system_clock::time_point timeStamp;
    bool is_dead;

public:
    PinTool(b2Body* body);
    virtual void handleCollision(Entity* entity) override;
    void die();
    bool isDead();
    void update();
};

#endif //PORTAL_PINTOOL_H
