/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameEngine.h
 * Author: t_filler
 *
 * Created on November 3, 2019, 6:44 PM
 */

#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Map.h"
#include "MapLoader.h"
#include "Dice.h"
#include "Cards.h"
#include "Player.h"
using std::vector;
using std::string;

class GameEngine {
public:
    GameEngine();
    GameEngine(const GameEngine& orig);
    virtual ~GameEngine();
    void SelectMaps();
    void Setup();
    void printTerritories();
    void mainGameLoop();
    void mainGameLoop(Map* MAP, std::vector<Player*> players);
private:
    Map* MAP;
    int N_players;
    Player* players;
    Deck* deck;
    vector<string> get_all_files_names_within_folder(string folder);
    
    
};

#endif /* GAMEENGINE_H */

