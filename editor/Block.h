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
    Block(std::string& path, Window& window, const std::string& name, int w, int h);
    ~Block();
    void removeFrom(int x, int y, std::map<std::pair<int, int>, std::string> &tiles) override;
};


#endif //PORTAL_BLOCK_H
