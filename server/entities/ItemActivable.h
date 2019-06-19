//
// Created by cecix on 15/06/19.
//

#ifndef PORTAL_ITEMACTIVABLE_H
#define PORTAL_ITEMACTIVABLE_H

#include "Entity.h"
#include "../../common/constants.h"

class ItemActivable: public Entity {
private:
    SwitchState state;

public:
    ItemActivable(std::string type, b2Body* body);

    /* Handles collision against other objects in the world */
    void handleCollision(Entity* entity) override;

    /* Returns a boolean that indicates if the object is active */
    bool isActive();

    /* Activates the object */
    void activate();

    /* Desactivates the object */
    void desactivate();

    /* Returns the state of the object */
    SwitchState getState();
};

#endif //PORTAL_ITEMACTIVABLE_H
