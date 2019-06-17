//
// Created by ndv on 6/13/19.
//

#include <iostream>
#include "StageManager.h"

StageManager::StageManager(int stageWidth,
        int stageHeight) :
        playerCounter(1),
        stage(Stage(stageWidth, stageHeight)){
    this->timeStamp = std::chrono::system_clock::now();
    // Parseo del YAML con la informaci[on del mapa acá.
    // Si o si necesitamos que nos pasen las medidas del mapa antes.
    // Por ahora hardcodeo un mapa.
    float xPosChell = 4;
    float yPosChell = 1;
    std::string idChell = "Chell1";
    std::string idChell2 = "Chell2";
    float xPosRock = 8;
    float yPosRock = 1;
    std::string idRock = "Rock1";
    float xPosCake = 2;
    float yPosCake = yPosChell + 12.5;

    float xPosAcid = 12;
    float yPosAcid = 1;
    std::string idAcid = "Acid1";

    stage.addBlock(CAKE_NAME, 1, xPosCake, yPosCake);
    // help pls
//    stage.addAcid(idAcid, ACID_HEIGHT, ACID_WIDTH,
//                  xPosAcid, yPosAcid);
    float metalBlockPosX = 0;
    float metalBlockPosY = 0;
    float metalSide = METAL_SIDE;
    for (int i = 0; i < 40; i += 2){
        stage.addBlock(METAL_BLOCK_NAME, metalSide, metalBlockPosX+i, metalBlockPosY);
    }
    std::string id_et = "EnergyTransmitter1";
    stage.addEnergyItem(ET_UP_NAME, id_et, METAL_SIDE, 8, 2);
    stage.addBlock(METAL_BLOCK_NAME, metalSide, metalBlockPosX + 2, metalBlockPosY + 12);
    stage.addBlock(METAL_BLOCK_NAME, metalSide, metalBlockPosX + 6, metalBlockPosY + 12);
    stage.addBlock(METAL_BLOCK_NAME, metalSide, metalBlockPosX + 8, metalBlockPosY + 6);
    stage.addBlock(METAL_BLOCK_NAME, metalSide, metalBlockPosX + 8, metalBlockPosY + 12);
    stage.addBlock(METAL_BLOCK_NAME, metalSide, metalBlockPosX + 12, metalBlockPosY + 12);
    stage.addBlock(METAL_BLOCK_NAME, metalSide, metalBlockPosX + 14, metalBlockPosY + 12);
    stage.addBlock(METAL_BLOCK_NAME, metalSide, metalBlockPosX + 16, metalBlockPosY + 12);
    stage.addBlock(METAL_BLOCK_NAME, metalSide, metalBlockPosX + 14, metalBlockPosY + 4);
    stage.addBlock(METAL_BLOCK_NAME, metalSide, metalBlockPosX + 16, metalBlockPosY + 4);
    stage.addBlock(METAL_BLOCK_NAME, metalSide, metalBlockPosX + 20, metalBlockPosY + 8);
    stage.addBlock(METAL_BLOCK_NAME, metalSide, metalBlockPosX + 2, metalBlockPosY + 6);
    stage.addChell(idChell, CHELL_HEIGHT, CHELL_WIDTH, xPosChell, yPosChell);
    stage.addChell(idChell2, CHELL_HEIGHT, CHELL_WIDTH, xPosChell + 20, yPosChell);

}

StageManager::~StageManager() {
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        it->second->stop();
        it->second->join();
        delete it->second;
    }
    for (auto it = clientQueues.begin(); it != clientQueues.end(); ++it) {
        delete it->second;
    }
}

void StageManager::run() {
    // We're gonna run a loop here, until a player wins the game or
    // everyone loses.
    // Also, I think it's a good idea to have the time step handled
    // here, because we can consume events between steps!
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        it->second->start();
    }
    bool weGaming = true;
    while (weGaming) {
        auto end = std::chrono::system_clock::now();
        auto difference = std::chrono::duration_cast<std::chrono::milliseconds>
                (end - timeStamp).count();
        if (difference <= 1000 / 60) {
            if (!userEventQueue.empty()){
                UserEvent userEvent = userEventQueue.pop();
                Chell* chell = stage.getChell(userEvent.getUserId());
                handleEvent(userEvent, chell);
            } else {
                std::this_thread::sleep_for (std::chrono::milliseconds(1));
            }
        } else {
            timeStamp = std::chrono::system_clock::now();
            stage.step();
            nlohmann::json stageStatus = stage.getCurrentState();
            // Check if any client is dead (disconnected).
            // If so, then delete his queue and the ClientHandler.
            for (auto it = clients.begin(); it != clients.end(); ){
                auto clientIt = it++;
                if (clientIt->second->isDead()) {
                    std::string playerID = clientIt->first;
                    std::cout << "Removing " + playerID << " from the client pool\n";
                    auto queueIt = clientQueues.find(playerID);
                    queueIt->second->push(THREAD_SUICIDE_PILL);
                    // Sanity check.
                    clientIt->second->stop();
                    clientIt->second->join();
                    delete queueIt->second;
                    clientQueues.erase(queueIt);
                    delete clientIt->second;
                    clients.erase(clientIt);
                    std::cout << "Client deleted\n";
                }
            }
            // Push stage status to each queue.
            // Doing a dump for each queue might be a performance hit.
            for (auto it = clientQueues.begin(); it != clientQueues.end(); it++) {
                it->second->push(stageStatus.dump());
            }
            // Provisory way to exit the loop.
            if (clients.size() == 0) {
                weGaming = false;
                std::cout << "Goodbye!\n";
            }
        }
    }
}

// This should use a factory but a switch will do for now.
void StageManager::handleEvent(UserEvent &userEvent,
        Chell *chell) {
    if (chell == nullptr || chell->hasWon()) return;
    std::string chell_id = userEvent.getUserId();
    int eventTypeCode = userEvent.getEventType();
    switch (eventTypeCode) {
        case USER_QUIT_CODE:
            // Kill Chell, I guess?
            break;
        case USER_JUMP_CODE:
            chell->jump();
            break;
        case USER_MOVE_LEFT_CODE:
            chell->moveLeft();
            break;
        case USER_MOVE_RIGHT_CODE:
            chell->moveRight();
            break;
        case USER_STOP_CODE:
            chell->stop();
            break;
        case USER_DROP_ROCK:
            chell->downloadRock();
            break;
        case USER_GRAB_ROCK:
            {
                float x_chell = chell->getHorizontalPosition();
                float y_chell = chell->getVerticalPosition();
                Rock *rock = stage.getClosestRock(x_chell, y_chell);
                chell->grabRock(rock);
            }
            break;
        case USER_BLUE_PORTAL_CODE:
            {
                float x_target = userEvent.getUserPosX();
                float y_target = userEvent.getUserPosY();
                Coordinate* target = new Coordinate(x_target, y_target);
                std::string id = chell_id;
                std::string replaced = "Chell";
                id.replace(0, replaced.length(), "BlueShot");
                stage.addShot(BLUE_SHOT_NAME, id, BULLET_HEIGHT, BULLET_WIDTH,
                        chell, target);
            }
            break;
        case USER_ORANGE_PORTAL_CODE:
            {
                float x_target = userEvent.getUserPosX();
                float y_target = userEvent.getUserPosY();
                Coordinate* target = new Coordinate(x_target, y_target);
                std::string id = chell_id;
                std::string replaced = "Chell";
                id.replace(0, replaced.length(), "OrangeShot");
                stage.addShot(ORANGE_SHOT_NAME, id, BULLET_HEIGHT, BULLET_WIDTH,
                                  chell, target);
            }
            break;
        case USER_THROW_ROCK:
            chell->releaseRock();
            break;
        case USER_REMOVE_PORTAL:
            chell->removePortals();
            break;
        default:
            break;
    }
}

// For now we'll receive x and y to position Chell in stage.
void StageManager::addPlayer(Socket &socket) {
    std::string playerID = PLAYER_ID_PREFIX + std::to_string(playerCounter);
    ++playerCounter;
    StageStatusQueue* newStatusQueue = new StageStatusQueue();
    clientQueues.insert({playerID, newStatusQueue});
    clients.insert({playerID, new ClientHandler(socket, userEventQueue, *newStatusQueue)});
}
