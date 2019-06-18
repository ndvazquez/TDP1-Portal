//
// Created by cecix on 17/06/19.
//

#ifndef PORTAL_YAMLPARSER_H
#define PORTAL_YAMLPARSER_H

#include <yaml-cpp/node/node.h>
#include "Stage.h"

class YamlParser {
private:
    YAML::Node editor_data;
    Stage& stage;
public:
    YamlParser(const std::string& path, Stage& stage);
    void parseAndAdd();
};

#endif //PORTAL_YAMLPARSER_H
