//
// Created by cecix on 22/06/19.
//

#define QUIT_ACTION "quit"
#define CREATE_ACTION "create"
#define JOIN_ACTION "join"


#include "Game.h"
#include <iostream>
#include "../json/json.hpp"
#include "../common/constants.h"

Game::Game(Protocol &clientProtocol, Socket &clientSocket):
    clientProtocol(clientProtocol), clientSocket(clientSocket) {
}

bool Game::play(std::string& idChell) {
    bool login = true;

    while (login) {
        // We'll first receive a list of games availables.
        std::string gaString = clientProtocol.receiveMessage();
        nlohmann::json gamesJson = nlohmann::json::parse(gaString);
        std::vector<std::string> gamesAvailable = gamesJson["games"].get<std::vector<std::string>>();
        if (gamesAvailable.empty()) {
            std::cout << "No games available at the moment, [create] one!\n";
        } else {
            std::cout << "List of games available: \n";
            for (auto & it : gamesAvailable) {
                std::cout << it << std::endl;
            }
        }
        std::cout << "Do you want to [create] or [join] a game? Type [quit] to leave.\n";
        std::string action;
        std::getline(std::cin, action);

        while (action != CREATE_ACTION && action != JOIN_ACTION && action != QUIT_ACTION) {
            std::cout << "Please enter a valid action.\n"
                         "Remember that you can [create] and [join] games or you can [quit].\n"
                         " Quitters ain't winners though!\n";
            std::getline(std::cin, action);
        }

        while (action == JOIN_ACTION && gamesAvailable.empty()) {
            std::cout << "It seems like you tried to [join] a non-existent game.\n"
                         "You might want to [create] one, or [quit].\n"
                         "But remember, quitters ain't winners!\n";
            std::getline(std::cin, action);
        }

        if (action == QUIT_ACTION) {
            clientSocket.shutdownAndClose();
            return false;
        }

        //We'll send the action to the server
        nlohmann::json actionJson;
        int actionCode;
        if (action == CREATE_ACTION) actionCode = CREATE_GAME_CODE;
        else if (action == JOIN_ACTION) actionCode = JOIN_GAME_CODE;
        actionJson["action"] = actionCode;
        std::string actionJsonString = actionJson.dump();
        clientProtocol.sendMessage(actionJsonString);

        std::string levelPath;
        if (action == CREATE_ACTION) {
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

        while (action == JOIN_ACTION && gaString.find(gameName) == std::string::npos) {
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

        if (action == CREATE_ACTION) {
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
