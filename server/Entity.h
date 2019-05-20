//
// Created by cecix on 19/05/19.
//

#ifndef PORTAL_ENTITY_H
#define PORTAL_ENTITY_H

#include <string>

class Entity {
protected:
    std::string type;

public:
    Entity(std::string type);
    std::string getType();
    virtual void handleCollision(Entity* entity) = 0;
};


#endif //PORTAL_ENTITY_H
