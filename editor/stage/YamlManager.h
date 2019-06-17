//
// Created by camix on 17/06/19.
//

#ifndef PORTAL_YAMLMANAGER_H
#define PORTAL_YAMLMANAGER_H

#include <yaml-cpp/node/node.h>
#include <unordered_map>
#include <map>
#include "object/Object.h"
#include "LogicGates.h"

class YamlManager {
public:
    void write(std::unordered_map<std::string, Object *> &textures,
               std::map<std::pair<int, int>, std::string> &tiles, int totalMeters);

    void read(Window &window,
              YAML::Node &texturesInfo,
              std::unordered_map<std::string, Object *> &textures,
              std::map<std::pair<int, int>, std::string> &tiles,
              LogicGates &logicGates);
};


#endif //PORTAL_YAMLMANAGER_H
