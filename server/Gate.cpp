//
// Created by cecix on 9/06/19.
//

#include <string>
#include "Gate.h"

Gate::Gate(b2Body* body, std::string logic,
          std::unordered_map<std::string, Button*> buttons) {
    this->body = body;
    this->logic = logic;
    this->buttons = buttons;
}

