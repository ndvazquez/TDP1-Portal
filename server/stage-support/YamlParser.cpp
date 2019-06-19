//
// Created by cecix on 17/06/19.
//

#include <yaml-cpp/yaml.h>
#include <iostream>

#include "YamlParser.h"

YamlParser::YamlParser(const std::string& path, Stage& stage):
    stage(stage) {
    editor_data = YAML::LoadFile(path);
}

void YamlParser::parseAndAdd() {
    int counter = 1;

    const YAML::Node& metal_blocks = editor_data[std::to_string(METAL_BLOCK)]["position"];
    for (YAML::const_iterator it = metal_blocks.begin(); it != metal_blocks.end(); it++) {
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        stage.addBlock(METAL_BLOCK_NAME, METAL_SIDE, x, y);
        static_json[std::to_string(counter)] = {
                {"type", METAL_BLOCK_NAME}, {"x", x}, {"y", y}
        };
        counter++;
    }

    const YAML::Node& brick_blocks = editor_data[std::to_string(ROCK_BLOCK)]["position"];
    for (YAML::const_iterator it = brick_blocks.begin();
         it != brick_blocks.end(); ++it) {
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        stage.addBlock(ROCK_BLOCK_NAME, METAL_SIDE, x, y);
        static_json[std::to_string(counter)] = {
                {"type", ROCK_BLOCK_NAME}, {"x", x}, {"y", y}
        };
        counter++;
    }

    int et_counter = 1;
    const YAML::Node& et_down = editor_data[std::to_string(LOUNCH_BLOCK_DOWN)]["position"];
    for (YAML::const_iterator it = et_down.begin();
         it != et_down.end(); ++it) {
        std::cout << "Soy un emisor" << std::endl;
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        std::string et_id = ET_NAME + std::to_string(et_counter);
        std::string eb_id = EB_NAME + std::to_string(et_counter);
        stage.addEnergyItem(ET_DOWN_NAME, et_id, METAL_SIDE, x, y);
        static_json[std::to_string(counter)] = {
                {"type", "LounchBlockDown"}, {"x", x}, {"y", y}
        };
        dynamic_json[eb_id] = {
                {"type", ENERGY_BALL__VIEW_CODE}, {"state", 0}, {"x", x}, {"y", y}
        };
        et_counter++;
        counter++;
    }

    const YAML::Node& et_up = editor_data[std::to_string(LOUNCH_BLOCK_UP)]["position"];
    for (YAML::const_iterator it = et_up.begin();
         it != et_up.end(); ++it) {
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        std::string et_id = ET_NAME + std::to_string(et_counter);
        std::string eb_id = EB_NAME + std::to_string(et_counter);
        stage.addEnergyItem(ET_UP_NAME, et_id, METAL_SIDE, x, y);
        static_json[std::to_string(counter)] = {
                {"type", "LounchBlockUp"}, {"x", x}, {"y", y}
        };
        dynamic_json[eb_id] = {
                {"type", ENERGY_BALL__VIEW_CODE}, {"state", 0}, {"x", x}, {"y", y}
        };
        et_counter++;
        counter++;
    }

    const YAML::Node& et_left = editor_data[std::to_string(LOUNCH_BLOCK_LEFT)]["position"];
    for (YAML::const_iterator it = et_left.begin();
         it != et_left.end(); ++it) {
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        std::string et_id = ET_NAME + std::to_string(et_counter);
        std::string eb_id = EB_NAME + std::to_string(et_counter);
        stage.addEnergyItem(ET_LEFT_NAME, et_id, METAL_SIDE, x, y);
        static_json[std::to_string(counter)] = {
                {"type", "LounchBlockLeft"}, {"x", x}, {"y", y}
        };
        dynamic_json[eb_id] = {
                {"type", ENERGY_BALL__VIEW_CODE}, {"state", 0}, {"x", x}, {"y", y}
        };
        et_counter++;
        counter++;
    }


    const YAML::Node& et_right = editor_data[std::to_string(LOUNCH_BLOCK_RIGHT)]["position"];
    for (YAML::const_iterator it = et_right.begin();
         it != et_right.end(); ++it) {
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        std::string et_id = ET_NAME + std::to_string(et_counter);
        std::string eb_id = EB_NAME + std::to_string(et_counter);
        stage.addEnergyItem(ET_RIGHT_NAME, et_id, METAL_SIDE, x, y);
        static_json[std::to_string(counter)] = {
                {"type", "LounchBlockRight"}, {"x", x}, {"y", y}
        };
        dynamic_json[eb_id] = {
                {"type", ENERGY_BALL__VIEW_CODE}, {"state", 0}, {"x", x}, {"y", y}
        };
        et_counter++;
        counter++;
    }

    int er_counter = 1;

    const YAML::Node& er_down = editor_data[std::to_string(RECEPTOR_DOWN)]["position"];
    for (YAML::const_iterator it = er_down.begin();
         it != er_down.end(); ++it) {
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        std::string id = ER_NAME + std::to_string(er_counter);
        stage.addEnergyItem(ER_DOWN_NAME, id, METAL_SIDE, x, y);
        /*dynamic_json[id] = {
                {"type", ER_DOWN_NAME}, {"state", OFF}, {"x", x}, {"y", y}
        };*/
        er_counter++;
    }

    const YAML::Node& er_up = editor_data[std::to_string(RECEPTOR_UP)]["position"];
    for (YAML::const_iterator it = er_up.begin();
         it != er_up.end(); ++it) {
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        std::string id = ER_NAME + std::to_string(er_counter);
        stage.addEnergyItem(ER_UP_NAME, id, METAL_SIDE, x, y);
       /* dynamic_json[id] = {
                {"type", ER_UP_NAME}, {"state", OFF}, {"x", x}, {"y", y}
        };*/
        er_counter++;
    }

    const YAML::Node& er_left = editor_data[std::to_string(RECEPTOR_LEFT)]["position"];
    for (YAML::const_iterator it = er_left.begin();
         it != er_left.end(); ++it) {
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        std::string id = ER_NAME + std::to_string(er_counter);
        stage.addEnergyItem(ER_LEFT_NAME, id, METAL_SIDE, x, y);
        /*dynamic_json[id] = {
                {"type", ER_LEFT_NAME}, {"state", OFF}, {"x", x}, {"y", y}
        };*/
        er_counter++;
    }

    const YAML::Node& er_right = editor_data[std::to_string(RECEPTOR_RIGHT)]["position"];
    for (YAML::const_iterator it = er_right.begin();
         it != er_right.end(); ++it) {
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        std::string id = ER_NAME + std::to_string(er_counter);
        stage.addEnergyItem(ER_RIGHT_NAME, id, METAL_SIDE, x, y);
       /* dynamic_json[id] = {
                {"type", ER_RIGHT_NAME}, {"state", OFF}, {"x", x}, {"y", y}
        };*/
        er_counter++;
    }

    const YAML::Node& diagonal_45 = editor_data[std::to_string(DIAGONAL_UP_LEFT)]["position"];
    for (YAML::const_iterator it = diagonal_45.begin();
         it != diagonal_45.end(); ++it) {
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        stage.addDiagonalBlock(METAL_SIDE, x, y, 45);
        static_json[std::to_string(counter)] = {
                {"type", DIAGONAL_METAL_BLOCK_45}, {"x", x}, {"y", y}
        };
        counter++;
    }

    const YAML::Node& diagonal_135 = editor_data[std::to_string(DIAGONAL_UP_RIGHT)]["position"];
    for (YAML::const_iterator it = diagonal_135.begin();
         it != diagonal_135.end(); ++it) {
        const YAML::Node &position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        stage.addDiagonalBlock(METAL_SIDE, x, y, 135);
        static_json[std::to_string(counter)] = {
                {"type", DIAGONAL_METAL_BLOCK_135}, {"x", x}, {"y", y}
        };
        counter++;
    }

    const YAML::Node& diagonal_225 = editor_data[std::to_string(DIAGONAL_DOWN_RIGHT)]["position"];
    for (YAML::const_iterator it = diagonal_225.begin();
         it != diagonal_225.end(); ++it) {
        const YAML::Node &position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        stage.addDiagonalBlock(METAL_SIDE, x, y, 225);
        static_json[std::to_string(counter)] = {
                {"type", DIAGONAL_METAL_BLOCK_225}, {"x", x}, {"y", y}
        };
        counter++;
    }

    const YAML::Node& diagonal_315 = editor_data[std::to_string(DIAGONAL_DOWN_LEFT)]["position"];
    for (YAML::const_iterator it = diagonal_315.begin();
         it != diagonal_315.end(); ++it) {
        const YAML::Node &position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        stage.addDiagonalBlock(METAL_SIDE, x, y, 315);
        static_json[std::to_string(counter)] = {
                {"type", DIAGONAL_METAL_BLOCK_315}, {"x", x}, {"y", y}
        };
        counter++;
    }

    int rock_counter = 1;
    const YAML::Node& rocks_1 = editor_data[std::to_string(ROCK1)]["position"];
    for (YAML::const_iterator it = rocks_1.begin();
         it != rocks_1.end(); ++it) {
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        std::string id = ROCK_NAME + std::to_string(rock_counter);
        stage.addRock(id, ROCK_WIDTH, x, y);
        dynamic_json[id] = {
                {"type", ROCK_VIEW_CODE}, {"state", 0}, {"x", x}, {"y", y}
        };
        rock_counter++;
    }

    const YAML::Node& rocks_2 = editor_data[std::to_string(ROCK2)]["position"];
    for (YAML::const_iterator it = rocks_2.begin();
         it != rocks_2.end(); ++it) {
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        std::string id = ROCK_NAME + std::to_string(rock_counter);
        stage.addRock(id, ROCK_WIDTH, x, y);
        dynamic_json[id] = {
                {"type", ROCK_VIEW_CODE}, {"state", 0}, {"x", x}, {"y", y}
        };
        rock_counter++;
    }

    const YAML::Node& rocks_3 = editor_data[std::to_string(ROCK3)]["position"];
    for (YAML::const_iterator it = rocks_3.begin();
         it != rocks_3.end(); ++it) {
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        std::string id = ROCK_NAME + std::to_string(rock_counter);
        stage.addRock(id, ROCK_WIDTH, x, y);
        dynamic_json[id] = {
                {"type", ROCK_VIEW_CODE}, {"state", 0}, {"x", x}, {"y", y}
        };
        rock_counter++;
    }

    int chell_counter = 1;
    const YAML::Node& chells = editor_data[std::to_string(CHELL)]["position"];
    for (YAML::const_iterator it = chells.begin();
         it != chells.end(); ++it) {
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        std::string chell_id = CHELL_NAME + std::to_string(chell_counter);
        std::string blue_shot_id = BLUE_SHOT_NAME + std::to_string(chell_counter);
        std::string orange_shot_id = ORANGE_SHOT_NAME + std::to_string(chell_counter);
        std::string blue_portal_id = BLUE_PORTAL_NAME + std::to_string(chell_counter);
        std::string orange_portal_id  = ORANGE_PORTAL_NAME + std::to_string(chell_counter);

        stage.addChell(chell_id, CHELL_HEIGHT, CHELL_WIDTH, x, y);
        dynamic_json[chell_id] = {
                {"type", CHELL_VIEW_CODE}, {"state", IDLE}, {"x", x}, {"y", y}
        };
        dynamic_json[blue_shot_id] = {
                    {"type", BULLET_VIEW_CODE}, {"state", 0}, {"x", x}, {"y", y}
        };
        dynamic_json[orange_shot_id] = {
                {"type", BULLET_VIEW_CODE}, {"state", 0}, {"x", x}, {"y", y}
        };
        dynamic_json[blue_portal_id] = {
                {"type", BLUE_PORTAL_VIEW_CODE}, {"state", 0}, {"x", x}, {"y", y}
        };
        dynamic_json[orange_portal_id] = {
                {"type", ORANGE_PORTAL_VIEW_CODE}, {"state", 0}, {"x", x}, {"y", y}
        };

        chell_counter++;
    }

    const YAML::Node& cake = editor_data[std::to_string(CAKE)]["position"];
    for (YAML::const_iterator it = cake.begin();
         it != cake.end(); ++it) {
        const YAML::Node &position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        stage.addBlock(CAKE_NAME, CAKE_HEIGHT, x, y);
        std::string id = "Cake";
        dynamic_json[id] = {
                {"type", CAKE_VIEW_CODE}, {"state", 0}, {"x", x}, {"y", y}
        };
    }

    int acid_counter = 1;
    const YAML::Node& acids = editor_data[std::to_string(ACID)]["position"];
    for (YAML::const_iterator it = acids.begin();
         it != acids.end(); ++it) {
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        std::string id = ACID_NAME + std::to_string(acid_counter);
        stage.addElement(ACID_NAME, id, ACID_HEIGHT, ACID_WIDTH, x, y);
        dynamic_json[id] = {
                {"type", ACID_VIEW_CODE}, {"state", 0}, {"x", x}, {"y", y}
        };
        acid_counter++;
    }

    const YAML::Node& gates = editor_data[std::to_string(GATE)]["position"];
    //TODO: missing logic

    int button_counter = 1;
    const YAML::Node& buttons = editor_data[std::to_string(BUTTON)]["position"];
    for (YAML::const_iterator it = buttons.begin();
         it != buttons.end(); ++it) {
        const YAML::Node& position = *it;
        float x = position["x"].as<float>();
        float y = position["y"].as<float>();
        std::string id = BUTTON_NAME + std::to_string(button_counter);
        stage.addElement(BUTTON_NAME, id, BUTTON_HEIGHT, BUTTON_WIDTH, x, y);
        dynamic_json[id] = {
                {"type", BUTTON_VIEW_CODE}, {"state", OFF}, {"x", x}, {"y", y}
        };
        button_counter++;
    }

}

nlohmann::json YamlParser::getStaticJson() {
    return static_json;
}

nlohmann::json YamlParser::getDynamicJson() {
    return dynamic_json;
}
