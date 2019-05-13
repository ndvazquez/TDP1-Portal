//
// Created by cecix on 13/05/19.
//

#ifndef PORTAL_ITEM_H
#define PORTAL_ITEM_H


#include <Box2D/Dynamics/b2Body.h>

class Item {
private:
    b2Body* body;
public:
    Item(b2Body* body);
};

#endif //PORTAL_ITEM_H
