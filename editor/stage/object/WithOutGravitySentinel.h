//
// Created by camix on 16/06/19.
//

#ifndef PORTAL_WITHOUTGRAVITYSENTINEL_H
#define PORTAL_WITHOUTGRAVITYSENTINEL_H


#include "StaticObject.h"

class WithOutGravitySentinel : public StaticObject {
public:
    WithOutGravitySentinel(std::string& path, Window& window, const std::string& name, int w, int h);
    ~WithOutGravitySentinel();
    void removeFrom(int x, int y, std::map<std::pair<int, int>, std::string> &tiles,
                    std::unordered_map<std::string, Object *>& map) override;

    bool hasGravity() override;
    void addTo(int x, int y, std::map<std::pair<int, int>,
            std::string> &tiles, std::unordered_map<std::string,
            Object *>& textures, bool needGravitySentinel = false) override;
    void draw(SDL_Rect* rec) override;
};


#endif //PORTAL_WITHOUTGRAVITYSENTINEL_H
