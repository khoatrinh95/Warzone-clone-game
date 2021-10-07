//
// Created by Khoa Trinh on 2021-09-29.
//

#ifndef COMP345_N11_GAMEENGINE_H
#define COMP345_N11_GAMEENGINE_H

#include "../cards/Cards.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class Player;
enum class Phases{START, MAPLOADED, MAPVALIDATED, PLAYERSADDED, ASSIGNREINFORCEMENT, ISSUEORDERS, EXECUTEORDERS, WIN};

extern Phases * phase;

class StartUp {
private:
    static void printTitle();
    static void addPlayers();
public:
    static void loadMap();
    static void validateMap();
    static void createPlayers();
    static void assignTerritories();
    static void startUp();
};

class Play {
private:
    static void printPlayPhaseGreeting();
public:
    static void assignArmies();
    static void issueOrders();
    static void executeOrders();
    static void cleanUp();
    static void playGame();
};

namespace HelperFunctions {
    void printOptions(vector<string>);
    bool isNumber(const std::string&);
    void takeInput(Phases);
}

class GameEngine
{
public:

    static Player* getOwnerOf(Territory* territory);
    static void assignToNeutralPlayer(Territory* territory);

private:

    static std::vector<Player*> players_;

};
#endif //COMP345_N11_GAMEENGINE_H
