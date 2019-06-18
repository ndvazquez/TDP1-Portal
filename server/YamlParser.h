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
    nlohmann::json dynamic_json;
    nlohmann::json static_json;

public:
    YamlParser(const std::string& path, Stage& stage);
    void parseAndAdd();
    nlohmann::json getDynamicJson();
    nlohmann::json getStaticJson();
};

#endif //PORTAL_YAMLPARSER_H
