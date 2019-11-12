#include "PlayerStrategies.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <limits>

void HumanPlayer::reinforce(Map* map, Player* player){
	std::cout << "Player Reinforcing" << std::endl;
	player->recuperateArmies(map);

	player->placeArmies(player->getArmies());

	std::cout << "Player Done Reinforcing" << std::endl;
}

void AggressiveComputer::reinforce(Map* map, Player* player){
	std::cout << "Aggressive Computer Reinforcing" << std::endl;
	player->recuperateArmies(map);

	//find land with most armies on
	int maxIndex = 0;
	for(std::vector<Territory>::size_type i=1; i<player->lands.size(); i++){
		if(player->lands[i]->getTroops() > player->lands[maxIndex]->getTroops()){
			maxIndex = i;
		}
	}
	//list all the countries
	int count = 0;
	for(std::vector<Territory>::size_type i = 0; i != player->lands.size(); i++) {
		count++;
		std::cout << count << ": " <<  player->lands[i]->getName() << "  Armies: " << player->lands[i]->getTroops() << std::endl;
	}
	player->lands[maxIndex]->incTroops(player->getArmies());
	std::cout << "Player has " << player->getArmies() << " armies and Aggressive Computer decided to reinforce " << player->lands[maxIndex]->getName() << std::endl;
	std::cout << "New total on " << player->lands[maxIndex]->getName() << " is " << player->lands[maxIndex]->getTroops() << std::endl;
	player->setArmies(0);
}

void BenevolentComputer::reinforce(Map* map, Player* player){
	std::cout << "Benevolent Computer Reinforcing" << std::endl;
	player->recuperateArmies(map);

	//find land with minimum armies
	int minIndex = 0;
	for(std::vector<Territory>::size_type i=1; i<player->lands.size(); i++){
		if(player->lands[i]->getTroops() < player->lands[minIndex]->getTroops()){
			minIndex = i;
		}
	}

	//list all the countries
	int count = 0;
	for(std::vector<Territory>::size_type i = 0; i != player->lands.size(); i++) {
		count++;
		std::cout << count << ": " <<  player->lands[i]->getName() << "  Armies: " << player->lands[i]->getTroops() << std::endl;
	}
	player->lands[minIndex]->incTroops(player->getArmies());
	std::cout << "Player has " << player->getArmies() << " armies and Benevolent Computer decided to reinforce " << player->lands[minIndex]->getName() << std::endl;
	std::cout << "New total on " << player->lands[minIndex]->getName() << " is " << player->lands[minIndex]->getTroops() << std::endl;
	player->setArmies(0);
}

PlayerStrategies::~PlayerStrategies(){
}

