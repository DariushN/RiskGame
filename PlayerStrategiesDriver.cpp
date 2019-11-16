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
	Map* MAP = MapLoader::MapBuilder("../Maps/risk.map");
	std::cout<<"Map name: " << MAP->getName() << endl;



	//Initialize some player objects
    std::string name1 = "AggressivePlayer";
    Player* player = new Player();
    player->setName(name1);
	std::cout << "Player Name: " << player->getName() << std::endl;
    //Initialize some player objects
    std::string name2= "HumanPlayer";
    Player* player2 = new Player();
    player2->setName(name2);
    std::cout << "Player Name: " << player2->getName() << std::endl;
    //Initialize some player objects
    std::string name3 = "BenevolantPlayer";
    Player* player3 = new Player();
    player3->setName(name3);
    std::cout << "Player Name: " << player3->getName() << std::endl;

	//give player some initial territories
	for(int i=0; i<10; i++) {
		MAP->Territories[i]->setOwner(player);
		MAP->Territories[i]->incTroops(i);
		player->lands.push_back(MAP->Territories[i]);
	}
	for(int i=10; i<30; i++) {
		MAP->Territories[i]->setOwner(player2);
		MAP->Territories[i]->incTroops(i);
		player2->lands.push_back(MAP->Territories[i]);
	}
    for(int i=30; i<42; i++) {
        MAP->Territories[i]->setOwner(player3);
        MAP->Territories[i]->incTroops(i);
        player3->lands.push_back(MAP->Territories[i]);
    }

	//player owns a hand of risk cards
	Deck* deck = new Deck(MAP->Territories);
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());

    deck->draw(player2->getHand());
    deck->draw(player2->getHand());
    deck->draw(player2->getHand());
    deck->draw(player2->getHand());
    deck->draw(player2->getHand());
    deck->draw(player2->getHand());

    deck->draw(player3->getHand());
    deck->draw(player3->getHand());
    deck->draw(player3->getHand());
    deck->draw(player3->getHand());
    deck->draw(player3->getHand());
    deck->draw(player3->getHand());

    // Setting strategies
	player->setStrategy(new AggressiveComputer());
	player2->setStrategy(new HumanPlayer());
	player3->setStrategy(new BenevolentComputer());
	player->reinforce(MAP);
    std::cout << "\n\n\n\n";
    player2->reinforce(MAP);
    std::cout << "\n\n\n\n";
    player3->reinforce(MAP);
    std::cout << "\n\n\n\n";
    player->attack(MAP);
    std::cout << "\n\n\n\n";

    //Changing strategy mid-play (switching strategy of player 2 and 3)
    player2->setStrategy(new BenevolentComputer());
    player3->setStrategy(new HumanPlayer());

    player2->attack(MAP);
    std::cout << "\n\n\n\n";
    player3->attack(MAP);
    std::cout << "\n\n\n\n";
    player->fortify();
    std::cout << "\n\n\n\n";
    player2->fortify();
    std::cout << "\n\n\n\n";
    player3->fortify();


}
