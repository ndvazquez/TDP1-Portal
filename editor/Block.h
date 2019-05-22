//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_BLOCK_H
#define PORTAL_BLOCK_H


#include "StaticObject.h"

class Block : public StaticObject {
public:
    Block(std::string& path, Window& window);
    ~Block();
    bool canBeOn(const std::string& name) override;
    bool canBeOn() override;
};


#endif //PORTAL_BLOCK_H
