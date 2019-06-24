//
// Created by cecix on 22/06/19.
//



#include "Game.h"
#include <iostream>
#include "../json/json.hpp"
#include "../common/constants.h"
#include "InitialMenu.h"

Game::Game(Protocol &clientProtocol, Socket &clientSocket, Window& window):
    clientProtocol(clientProtocol), clientSocket(clientSocket), window(window) {
}

bool Game::play(std::string& idChell) {
    bool login = true;

    while (login) {
        // We'll first receive a list of games availables.
        std::string gaString = clientProtocol.receiveMessage();
        nlohmann::json gamesJson = nlohmann::json::parse(gaString);
        std::vector<std::string> gamesAvailable = gamesJson["games"].get<std::vector<std::string>>();


        std::string action;
        int rst;

        InitialMenu menu(window, gamesAvailable);
        rst = menu.start();

        if (rst == QUIT_ACTION) {
            std::cerr << "QUIT" << std::endl;
            clientSocket.shutdownAndClose();
            return false;
        }

        //We'll send the action to the server
        nlohmann::json actionJson;
        int actionCode;
        if (rst == CREATE_ACTION) {
            std::cerr << "CREATE" << std::endl;
            actionCode = CREATE_GAME_CODE;
        }
        else if (rst == JOIN_ACTION){
            std::cerr << "JOIN" << std::endl;
            actionCode = JOIN_GAME_CODE;
        }
        actionJson["action"] = actionCode;
        std::string actionJsonString = actionJson.dump();
        clientProtocol.sendMessage(actionJsonString);

        std::string levelPath;
        if (rst == CREATE_ACTION) {
            // Receive the available levels
            std::string laString = clientProtocol.receiveMessage();
            nlohmann::json levelsJson = nlohmann::json::parse(laString);
            std::vector<std::string> levelsAvailable = levelsJson["levels"].get<std::vector<std::string>>();
            if (levelsAvailable.empty()) {
                std::cout << "No levels available at the moment, create one with the editor!\n";
                clientSocket.shutdownAndClose();
                return false;
            } else {
                std::cout << "List of levels available: \n";
                for (auto & it : levelsAvailable) {
                    std::cout << it << std::endl;
                }
            }
            std::cout << "Choose a level by typing its name: \n";
            std::getline(std::cin, levelPath);
            while (laString.find(levelPath) == std::string::npos) {
                std::cout << "Please enter a valid level name: \n";
                std::getline(std::cin, levelPath);
            }
            if (levelPath.find(".yaml") == std::string::npos) {
                levelPath += ".yaml";
            }
        }
        // Prepare other fields needed to process
        std::cout << "Enter game name: \n";
        std::string gameName;
        std::getline(std::cin, gameName);

        while (rst == JOIN_ACTION && gaString.find(gameName) == std::string::npos) {
            std::cout << "The game you are looking for doesn't exist. "
                         "Please enter one of the games available: \n";
            std::getline(std::cin, gameName);
        }

        std::cout << "Enter your ID: \n";
        std::string playerId;
        std::getline(std::cin, playerId);

        nlohmann::json fieldsJson;

        fieldsJson["gameName"] = gameName;
        fieldsJson["id"] = playerId;
        std::string fieldJsonString = fieldsJson.dump();

        // Send the other fields to the server
        clientProtocol.sendMessage(fieldJsonString);

        if (rst == CREATE_ACTION) {
            // Send the level path to the client.
            clientProtocol.sendMessage(levelPath);
        }
        std::cout << "Waiting response from server...\n";

        std::string serverResponse = clientProtocol.receiveMessage();
        nlohmann::json serverResponseJson = nlohmann::json::parse(serverResponse);
        int responseCode = serverResponseJson["result"].get<int>();
        std::cout << serverResponseJson["desc"].get<std::string>() << std::endl;
        if (responseCode == SUCCESS_CODE) {
            idChell = serverResponseJson["idChell"].get<std::string>();
            login = false;
        }
        else {
            std::cout << "The ID you've just entered already exists! \n";
        }
    }
    return true;
}
