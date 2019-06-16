//
// Created by camix on 15/06/19.
//

#ifndef PORTAL_RECEPTOR_H
#define PORTAL_RECEPTOR_H

#include <map>
#include "../../../common/Window.h"
#include "StaticObject.h"

#define RECEPTOR_SENTINEL "KindOfARock"

class Receptor : public StaticObject {
private:
    std::map<std::pair<int, int>, std::string> names;

public:
    Receptor(std::string &path, Window &window, const std::string& name, int w, int h);
    ~Receptor();
    void setName(std::pair<int, int>& position, std::string& enteredName) override;
    bool doesThisNameExist(std::string &string) override;
    void removeFrom(int x, int y, std::map<std::pair<int, int>, std::string> &tiles,
                    std::unordered_map<std::string, Object *> &textures) override;
    bool hasGravity() override;
};


#endif //PORTAL_RECEPTOR_H
