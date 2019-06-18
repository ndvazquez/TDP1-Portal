//
// Created by camix on 16/06/19.
//

#ifndef PORTAL_GRAVITYSENTINEL_H
#define PORTAL_GRAVITYSENTINEL_H


#include "StaticObject.h"

class GravitySentinel : public StaticObject {
public:
    GravitySentinel(std::string &path, Window &window, int id, int w, int h);
    ~GravitySentinel();
    void removeFrom(int x, int y, std::map<std::pair<int, int>, int> &tiles,
                    std::unordered_map<int, Object *> &textures) override;

    bool hasGravity() override;
    void addTo(int x, int y, std::map<std::pair<int, int>, int> &tiles, std::unordered_map<int, Object *> &textures,
               bool needGravitySentinel = false) override;
    void draw(SDL_Rect* rec) override;
    std::pair<float, float> MatrixPosToCenterOfMass(const std::pair<int, int> &position) override;

};


#endif //PORTAL_GRAVITYSENTINEL_H
