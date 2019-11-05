
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
    GameEngine(); // Default constructor
    GameEngine(const GameEngine& orig); // Copy constructor
    virtual ~GameEngine(); // Destructor
    void SelectMaps(); // Allow the user to select a map
    void Setup(); // Set up players and territories
    void printTerritories();
    bool compliesWithA2Q2(); // Check if game was set up correctly
    void mainGameLoop(); // Allow a player to make a move (reinforce, attack, fortify)
    void mainGameLoop(Map* MAP, std::vector<Player*> players); // Overloaded game loop
private:
    Map* MAP; // User-selected map
    int N_players; // Number of players
    Player* players; // Array of players
    Deck* deck;
    vector<string> get_all_files_names_within_folder(string folder); // Vector of file names within directory
    
    
};

#endif /* GAMEENGINE_H */

