//
// Created by camix on 22/05/19.
//

#ifndef PORTAL_GATE_H
#define PORTAL_GATE_H

#include <map>
#include "StaticObject.h"

class Gate : public StaticObject {
private:
    std::map<std::pair<int, int>, std::string> names;
    std::map<std::pair<int, int>, std::string> conditions;

public:
    Gate(std::string &path, Window &window, int id, int w, int h);
    ~Gate();

    void setName(std::pair<int, int>& position, std::string& enteredName) override;
    void addTo(int x, int y, std::map<std::pair<int, int>, int> &tiles, std::unordered_map<int, Object *> &textures,
               bool needGravitySentinel = false) override;
    void removeFrom(int x, int y, std::map<std::pair<int, int>, int> &tiles,
                    std::unordered_map<int, Object *> &textures) override;
    void addCondition(std::pair<int, int> position, std::string& condition) override;
    bool hasCondition() override;

    std::pair<float, float> MatrixPosToCenterOfMass(const std::pair<int, int> &position) override;

    std::map<std::pair<int, int>, std::string> &getNames() override;
};


#endif //PORTAL_GATE_H
