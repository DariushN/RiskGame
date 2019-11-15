#include <iostream>
#include "Player.h"
#include "MapLoader.h"
#include "PlayerStrategies.h"
#include "Map.h"
#include "Cards.h"
class AggressiveComputer;
class BenevolentComputer;
class HumanPlayer;

using namespace std;

int main(int argc, char** argv) {
	//get a map for demonstration purposes
	Map* MAP = MapLoader::MapBuilder("Maps/risk.map");
	std::cout<<"Map name: " << MAP->getName() << endl;



	//Initialize some player objects
	std::string name1 = "Player1";
	Player* player = new Player();
	player->setName(name1);
	std::cout << "Player Name: " << player->getName() << std::endl;

	//give player some initial territories
	for(int i=0; i<4; i++) {
		MAP->Territories[i]->setOwner(player);
		MAP->Territories[i]->incTroops(i);
		player->lands.push_back(MAP->Territories[i]);
	}
	for(int i=20; i<25; i++) {
		MAP->Territories[i]->setOwner(player);
		MAP->Territories[i]->incTroops(i);
		player->lands.push_back(MAP->Territories[i]);
	}

	//player owns a hand of risk cards
	Deck* deck = new Deck(MAP->Territories);
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());

	player->setStrategy(new HumanPlayer());
	player->reinforce(MAP);
	std::cout << "\n\n";
	player->setStrategy(new AggressiveComputer());
	player->reinforce(MAP);
	std::cout << "\n\n";
	player->setStrategy(new BenevolentComputer());
	player->reinforce(MAP);
	std::cout << "\n\n";
}
