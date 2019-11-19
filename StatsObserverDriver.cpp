#include "GameObserver.h"
#include "GameEngine.h"
#include "MapLoader.h"

using namespace std;


int main(int argc, char** argv) {


	// Get a map for demonstration purposes
	MapLoader* mapLoader = new MapLoader();
	Map* MAP = mapLoader->MapBuilder("Maps/risk.map");
	std::cout << "Map name: " << MAP->getName() << endl;

	// Initialize 2 player objects
	std::string name1 = "P1";
	std::string name2 = "P2";
	// Add both players to an array
	Player* players = new Player[2];
	players[0].setName(name1);
	players[1].setName(name2);
	std::cout << "Player Name: " << players[0].getName() << std::endl;
	std::cout << "Player Name: " << players[1].getName() << std::endl;

	// Give the players an equal amount of initial territories
	for (int i = 0; i < 10; i++) {
		MAP->Territories[i]->setOwner(&players[0]);
		MAP->Territories[i]->incTroops(i);
		players[0].lands.push_back(MAP->Territories[i]);
	}
	for (int i = 10; i < 42; i++) {
		MAP->Territories[i]->setOwner(&players[1]);
		MAP->Territories[i]->incTroops(i);
		players[1].lands.push_back(MAP->Territories[i]);
	}


	// Set strategy for both players
	players[0].setStrategy(new HumanPlayer());
	players[1].setStrategy(new HumanPlayer());

	// Assign hand of risk cards
	Deck* deck = new Deck(MAP->Territories);
	deck->draw(players[0].getHand());
	deck->draw(players[0].getHand());
	deck->draw(players[0].getHand());
	deck->draw(players[0].getHand());
	deck->draw(players[0].getHand());
	deck->draw(players[0].getHand());

	Deck* deck2 = new Deck(MAP->Territories);
	deck->draw(players[1].getHand());
	deck->draw(players[1].getHand());
	deck->draw(players[1].getHand());
	deck->draw(players[1].getHand());
	deck->draw(players[1].getHand());
	deck->draw(players[1].getHand());


	// Create GameEngine object
	GameEngine gameEngine(MAP, players, 2);

	// Create observers
	GameObserver GO(&players[0]);
	GameObserver GO2(&players[1]);
	StatsObserver SO(&gameEngine);

	// Start game

	gameEngine.mainGameLoop();

	return 0;

}


