//
// Created by cecix on 9/06/19.
//

#include <string>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "Gate.h"
#include "BlueShot.h"
#include "OrangeShot.h"

Gate::Gate(b2Body* body, std::string logic,
          std::unordered_map<std::string, ItemActivable*> items):
          Entity(GATE_NAME, body) {
    this->logic = logic;
    this->items = items;
    this->state = CLOSED;
    this->replaced = "";
}

bool evaluateSubString(std::string str) {
    bool variable = true;
    bool multiply = false;
    bool add = false;
    bool negation = false;
    for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
        bool to_evaluate;
        if (*it == '&') {
            multiply = true;
            continue;
        }
        if (*it == '|') {
            add = true;
            continue;
        }
        if (*it == '!') {
            negation = true;
            continue;
        }
        if (*it == ' ') continue;
        if (*it == '1') {
            to_evaluate = true;
        }
        if (*it == '0') {
            to_evaluate = false;
        }
        if (! add & ! multiply) {
            if (negation) {
                variable = ! to_evaluate;
                negation = false;
            } else {
                variable = to_evaluate;
            }
        }
        if (multiply) {
            if (negation) {
                to_evaluate = ! to_evaluate;
                negation = false;
            }
            variable *= to_evaluate;
            multiply = false;
        }
        if (add) {
            if (negation) {
                to_evaluate = ! to_evaluate;
                negation = false;
            }
            variable += to_evaluate;
            add = false;
        }
    }
    return variable;
}

bool Gate::parseBool() {
    bool variable = true;
    std::string substr = "";
    bool multiply = false;
    bool add = false;
    bool parenthesis = false;
    bool skip = false;
    bool negation = false;
    for (std::string::iterator it = replaced.begin(); it != replaced.end(); ++it) {
        bool to_evaluate;
        if (*it == '(') {
            parenthesis = true;
            continue;
        }
        if (*it == ')') {
            parenthesis = false;
        }

        if (parenthesis) {
            substr += *it;
            continue;
        }
        if (substr.length() != 0 && ! parenthesis) {
            to_evaluate = evaluateSubString(substr);
            skip = true;
            substr = "";
        }
        if (*it == '&') {
            multiply = true;
            continue;
        }
        if (*it == '|') {
            add = true;
            continue;
        }
        if (*it == '!') {
            negation = true;
            continue;
        }
        if (*it == ' ') continue;
        if (*it == '1' && ! skip) {
            to_evaluate = true;
        }
        if (*it == '0' && ! skip) {
            to_evaluate = false;
        }
        if (! add & ! multiply && ! skip) {
            if (negation) {
                variable = ! to_evaluate;
                negation = false;
            } else {
                variable = to_evaluate;
            }
        }
        if (multiply) {
            if (negation) {
                to_evaluate = ! to_evaluate;
                negation = false;
            }
            variable *= to_evaluate;
            multiply = false;
        }
        if (add) {
            if (negation) {
                to_evaluate = ! to_evaluate;
                negation = false;
            }
            variable += to_evaluate;
            add = false;
        }
    }
    return variable;
}

void Gate::update() {
    // Replace the logic string with 0 and 1 according to button state
    replaced = logic;
    for (auto i = items.begin(); i != items.end(); i++) {
        std::string id = i->first;
        bool isActive = i->second->isActive();
        size_t length_id = id.length();
        size_t i_id = replaced.find(id);
        if (i_id == std::string::npos) break;
        std::string to_replace;
        if (isActive) {
            to_replace = "1";
        } else {
            to_replace = "0";
        }
        replaced.replace(i_id, length_id, to_replace);
    }
    // Obtain boolean from string
    if (! parseBool()) {
        this->state = CLOSED;
        body->SetActive(true);
    } else {
        this->state = OPEN;
        body->SetActive(false);
    }
}

GateState Gate::getState() {
    return state;
}

void Gate::handleCollision(Entity* entity) {
    std::string type = entity->getType();
    if (type == BLUE_SHOT_NAME) {
        static_cast<BlueShot*>(entity)->die();
    }
    if (type == ORANGE_SHOT_NAME) {
        static_cast<OrangeShot*>(entity)->die();
    }
}
