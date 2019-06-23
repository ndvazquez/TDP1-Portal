//
// Created by cecix on 22/06/19.
//

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
            std::cout << "No games available at the moment, create one!\n";
        } else {
            std::cout << "List of games available: \n";
            for (auto & it : gamesAvailable) {
                std::cout << it << std::endl;
            }
        }
        // TODO: Gotta validate the user input.
        std::cout << "Do you want to [create] or [join] a game? Type [quit] to leave.\n";
        std::string action;
        std::getline(std::cin, action);
        if (action == "quit") {
            clientSocket.shutdownAndClose();
            return false;
        }
        std::string levelPath;
        if (action == "create") {
            std::cout << "Enter the level path: \n";
            std::getline(std::cin, levelPath);
        }
        std::cout << "Enter game name: \n";
        std::string gameName;
        std::getline(std::cin, gameName);
        std::cout << "Enter your ID: \n";
        std::string playerId;
        std::getline(std::cin, playerId);
        // Gotta check that no field is null, etc.
        nlohmann::json actionJson;
        int actionCode;
        if (action.compare("create") == 0) actionCode = CREATE_GAME_CODE;
        else if (action.compare("join") == 0) actionCode = JOIN_GAME_CODE;
        actionJson["action"] = actionCode;
        actionJson["gameName"] = gameName;
        actionJson["id"] = playerId;
        std::string actionJsonString = actionJson.dump();
        clientProtocol.sendMessage(actionJsonString);
        if (action == "create") {
            clientProtocol.sendMessage(levelPath);
        }
        std::cout << "Waiting response from server...\n";

        std::string serverResponse = clientProtocol.receiveMessage();
        nlohmann::json serverResponseJson = nlohmann::json::parse(serverResponse);
        int responseCode = serverResponseJson["result"].get<int>();
        std::cout << serverResponseJson["desc"].get<std::string>() << std::endl;
        if (responseCode == SUCCESS_CODE) {
            idChell = serverResponseJson["idChell"].get<std::string>();
            std::cout << "Id chell asignada: " << idChell << std::endl;
            login = false;
        }
    }
    return true;
}
