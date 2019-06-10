//
// Created by cecix on 9/06/19.
//

#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "Gate.h"

Gate::Gate(b2Body* body, std::string logic,
          std::unordered_map<std::string, Button*> buttons) {
    this->body = body;
    this->logic = logic;
    this->buttons = buttons;
    this->open = false;
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
    for (std::string::iterator it = logic.begin(); it != logic.end(); ++it) {
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

void Gate::handleGate() {
    body->SetActive(false); //So Chell could traspass the object
    auto end = std::chrono::system_clock::now();
    auto difference = std::chrono::duration_cast<std::chrono::milliseconds>
            (end - timeStamp).count();
    if (difference <= 3000) return; //3 seconds to open the gate
    timeStamp = std::chrono::system_clock::now();

    body->SetActive(true);
}

void Gate::update() {
    // Replace the logic string with 0 and 1 according to button state
    for (auto i = buttons.begin(); i != buttons.end(); i++) {
        std::string id = i->first;
        bool isActive = i->second->isActive();
        size_t length_id = id.length();
        size_t i_id = logic.find(id);
        std::string to_replace;
        if (isActive) {
            to_replace = "1";
        } else {
            to_replace = "0";
        }
        logic.replace(i_id, length_id, to_replace);
    }

    // Obtain boolean from string
    open = parseBool();
    if (open) handleGate();
}

bool Gate::isOpen() {
    return open;
}

