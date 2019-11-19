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
	Player* player = new Player();
	Player* player2 = new Player();
	player->setName(name1);
	player2->setName(name2);
	std::cout << "Player Name: " << player->getName() << std::endl;
	std::cout << "Player Name: " << player2->getName() << std::endl;

	// Give the players some initial territories
	for (int i = 0; i < 21; i++) {
		MAP->Territories[i]->setOwner(player);
		MAP->Territories[i]->incTroops(i);
		player->lands.push_back(MAP->Territories[i]);
	}
	for (int i = 21; i < 42; i++) {
		MAP->Territories[i]->setOwner(player2);
		MAP->Territories[i]->incTroops(i);
		player2->lands.push_back(MAP->Territories[i]);
	}

	// Set strategy for both players
	player->setStrategy(new HumanPlayer());
	player2->setStrategy(new HumanPlayer());

	// Assign hand of risk cards
	Deck* deck = new Deck(MAP->Territories);
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());

	Deck* deck2 = new Deck(MAP->Territories);
	deck->draw(player2->getHand());
	deck->draw(player2->getHand());
	deck->draw(player2->getHand());
	deck->draw(player2->getHand());
	deck->draw(player2->getHand());
	deck->draw(player2->getHand());

	// Add both players to a vector
	std::vector<Player*> players;
	players.push_back(player);
	players.push_back(player2);
	int size = players.size();

	// Create observers
	GameObserver GO = GameObserver(players[0]);
	GameObserver GO2 = GameObserver(players[1]);

	// Start game
	GameEngine gameEngine;
	gameEngine.mainGameLoop(MAP, players);

	return 0;
}

