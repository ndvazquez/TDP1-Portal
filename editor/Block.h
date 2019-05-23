//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_BLOCK_H
#define PORTAL_BLOCK_H


#include "StaticObject.h"
#include "Button.h"
#include "Chell.h"
#include "Gate.h"
#include "Rock.h"

class Block : public StaticObject {
public:
    Block(const std::string& path, Window& window, const std::string& name);
    ~Block();
    bool canBeOn(const std::string& name) override;
    bool canBeOn() override;
};


#endif //PORTAL_BLOCK_H
