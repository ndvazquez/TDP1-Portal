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
    nlohmann::json metadata_json;

public:
    YamlParser(const std::string& path, Stage& stage);

    /* Reads a YAML and parse it in order to fill the stage */
    void parseAndAdd();

    /* Returns a JSON with the data of the objects identified by an id */
    nlohmann::json getDynamicJson();

    /* Returns a JSON with the data of the blocks */
    nlohmann::json getStaticJson();

    /* Returns a JSON with metatada */
    nlohmann::json getMetadataJson();
};

#endif //PORTAL_YAMLPARSER_H
