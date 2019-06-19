//
// Created by cecix on 17/05/19.
//

#ifndef PORTAL_BUTTON_H
#define PORTAL_BUTTON_H

#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"
#include "../../common/constants.h"
#include "movements/Dynamic.h"
#include "ItemActivable.h"

class Button: public ItemActivable {
private:
    Dynamic dynamic;

public:
    explicit Button(b2Body* body);

    /* Handles collision against other objects in the world */
    void handleCollision(Entity* entity) override;

    /* Updates state of the button: on and off */
    void update();
};

#endif //PORTAL_BUTTON_H
