//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_ROCK_H
#define PORTAL_ROCK_H


#include "../common/Window.h"
#include "StaticObject.h"

class Rock : public StaticObject {
public:
    Rock(const std::string& path, Window& window, const std::string& name);
    ~Rock();
    bool canBeOn() override;
    void addTo(int x, int y, std::map<std::pair<int, int>, std::string>& tiles) override;
};


#endif //PORTAL_ROCK_H
