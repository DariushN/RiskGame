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
#include "GameObserver.h"
using std::vector;
using std::string;

class Subject;

class GameEngine : public Subject{
public:
	GameEngine(); // Default constructor
	GameEngine(const GameEngine& orig);
	GameEngine(Map* MAP, Player* players, int n);
	GameEngine& operator=(const GameEngine& orig);
	virtual ~GameEngine(); // Destructor
	void SelectMaps(); // Allow the user to select a map
	void Setup(); // Set up players and territories
	void printTerritories();
	Player* getPlayers() {
		return players;
	}
	int getNumPlayers() {
		return N_players;
	}
	Map* getMap() {
		return MAP;
	}
	Player* getTurn(){
		return turn;
	}
	void setTurn(Player p){
		turn = &p;
	}
	string getPhase() {
		return *phase;
	}

	void setPhase(std::string p) {
		*phase = p;
	}
        void begin();
	void mainGameLoop(); // Allow a player to make a move (reinforce, attack, fortify)
	void mainGameLoop(Map* MAP, std::vector<Player*> players); // Overloaded game loop
private:
	Map* MAP; // User-selected map
	int N_players; // Number of players
	Player* players; // Array of players
	Deck* deck;
	Player* turn;
	vector<string> get_all_files_names_within_folder(string folder); // Vector of file names within directory
    string* phase;
    string TournamentGameLoop(Map* m,Player* p, int n_turns);
    
};

#endif /* GAMEENGINE_H */

