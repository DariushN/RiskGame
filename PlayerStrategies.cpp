#include "PlayerStrategies.h"
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <limits>
#include <vector>

void HumanPlayer::reinforce(Map* map, Player* player){
	std::cout << "Player Reinforcing" << std::endl;
	player->recuperateArmies(map);

	player->placeArmies(player->getArmies());

	std::cout << "Player Done Reinforcing" << std::endl;
}

void HumanPlayer::fortify(Player* player){
	std::cout << "Human player fortifying" << std::endl;
	bool deciding = true;
	bool fortifying = true;

	while(deciding) {
		int count = 1;
		//print out all players territories and number of armies on each
		for(std::vector<Territory>::size_type i = 0; i != player->lands.size(); i++) {
			std::cout << count << ": " <<  player->lands[i]->getName() << "     Armies: " << player->lands[i]->getTroops() << std::endl;
			count++;
		}

		std::cout << "would you like to fortify a position? y or n" << std::endl;
		char input;
		cin >> input;
		if(input == 'n'){
			break;
		} else if(input != 'y') {
			std::cout << "please enter y or n to proceed" << std::endl;
			continue;
		}
		// player decides to fortify

		//Print out all the territories and and their adjacent territories
		count = 1;
		for(std::vector<Territory>::size_type i = 0; i != player->lands.size(); i++) {
			std::cout << count << ": " <<  player->lands[i]->getName() << "  Armies: " <<
					player->lands[i]->getTroops() << std::endl;
			player->printAdjacentCountries(player->lands[i]->adjacents);
			count++;
		}

		while(fortifying) {
			std::cout << "Enter the country number you would like to move your armies from or type -1 to end fortification"  << std::endl;
			int country1;
			cin >> country1;
			while(std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
				std::cout << "Please Enter a number: ";
				std::cin >> country1;
			}

			if(country1 == -1) break;

			std::cout << "Enter the country you would like to fortify or type -1 to end fortification" << std::endl;
			int country2;
			std::cin >> country2;
			while(std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
				std::cout << "Please Enter a number: ";
				std::cin >> country2;
			}
			if(country2 == -1) break;

			//validation on countries picked
			if(country1 > count || country2 < 1) {
				std::cout << "Please pick a valid starting country" << std::endl;
				continue;
			} else if(country2 > count || country2 < 1) {
				std::cout << "Please pick a valid country to fortify" << std::endl;
				continue;
			} else if(country1 == country2) {
				std::cout << "Please pick different countries" << std::endl;
				continue;
			} else if(player->lands[country1 - 1]->getTroops() <= 1) {
				std::cout << "Starting country must have more than 1 army, please pick another country" << std::endl;
				continue;
			} else if(!player->lands[country1 - 1]->isAdj(player->lands[country2 - 1])) {
				std::cout << "please pick countries that are adjacent" << std::endl;
				continue;
			}

			//loop to get number of troops that user wants to move
			while(1) {
				std::cout << "how many troops would you like to move from " << player->lands[country1 - 1]->getName()
						<< " to " << player->lands[country2 - 1]->getName() << std::endl;

				int troops;
				cin >> troops;
				while(std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
					std::cout << "Please Enter a number: ";
					std::cin >> troops;
				}

				if(troops > player->lands[country1 - 1]->getTroops() - 1) { //must leave at least 1 troop on the territory
					std::cout << "Please pick a number less than "<< player->lands[country1 - 1]->getTroops() << std::endl;
					continue;
				} else if (troops < 1){
					std::cout << "Please enter a valid number" << std::endl;
				}else {
					//increment troops on territory chosen
					player->lands[country2 - 1]->incTroops(troops);
					//decrement troops on country where armies are traded
					player->lands[country1 - 1]->decTroops(troops);

					std::cout << "Fortified " << player->lands[country2 - 1]->getName() << ", new total is " << player->lands[country2 - 1]->getTroops() << std::endl;
					break;
				}
			}
			break;
		}
		break;
	}

	std::cout << "Fortification done" << std::endl;
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

void AggressiveComputer::fortify(Player* player){
	//finds the biggest possible move among all the possible countries that a user owns
	std::cout << "Aggressive Computer fortifying" << std::endl;
	int count = 1;
	for(std::vector<Territory>::size_type i = 0; i != player->lands.size(); i++) {
		std::cout << count << ": " <<  player->lands[i]->getName() << "  Armies: " <<
				player->lands[i]->getTroops() << std::endl;
		player->printAdjacentCountries(player->lands[i]->adjacents);
		count++;
	}

	int mostTroops = 0;
	int country1 = -1;
	int country2 = -1;
	for(std::vector<Territory>::size_type i=0; i<player->lands.size(); i++){
		for(std::vector<Territory>::size_type j=0; j<player->lands[i]->adjacents.size(); j++){
			//check if bigger than mostTroops
			if(player->lands[i]->getTroops() + (player->lands[i]->adjacents[j]->getTroops() - 1) > mostTroops && player->lands[i]->adjacents[j]->getOwner() != NULL){
				//check if player owns adjacent country and also if both countries have more than 1 troop
				if(player->lands[i]->adjacents[j]->getOwner()->getName() == player->getName() && player->lands[i]->getTroops() > 1 && player->lands[i]->adjacents[j]->getTroops() > 1){
					country1 = i;
					country2 = j;
					mostTroops = player->lands[i]->getTroops() + (player->lands[i]->adjacents[j]->getTroops() - 1);
				}
			}
		}
	}

	//check if indexes were set
	if(country1 == -1 || country2 == -1){
		std::cout << "Aggressive did not fortify" << std::endl;
		return;
	}

	std::cout << "Aggressive computer decided to move " << player->lands[country1]->adjacents[country2]->getTroops() - 1 << " armies from " <<
				player->lands[country1]->adjacents[country2]->getName() << " to " << player->lands[country1]->getName() << std::endl;

	//increment troops on territory chosen
	player->lands[country1]->incTroops(player->lands[country1]->adjacents[country2]->getTroops() - 1);
	//set the adjacent countries troops back down to 1
	player->lands[country1]->adjacents[country2]->setTroops(1);

	std::cout << "Aggressive Computer Fortified " << player->lands[country1]->getName() << ", new total is " << player->lands[country1]->getTroops() << std::endl;
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

struct comparisonClass {
  bool operator() (Territory*& i,Territory*& j) { return (i->getTroops()<j->getTroops());}
} comparisonFunction;

void BenevolentComputer::fortify(Player* player){
	//Benevolant computer will find the country with min armies and check if it has adjacent countries that can move armies
	//if there are no potential adjacent countries, then it moves to second smallest country
	//it then moves half the armies of the biggest adjacent country to the smallest country
	std::cout << "Benevolant Computer fortifying" << std::endl;
	std::vector<Territory*> territories = player->lands;
	int count = 1;
	for(std::vector<Territory>::size_type i = 0; i != territories.size(); i++) {
		std::cout << count << ": " <<  territories[i]->getName() << "  Armies: " <<
				territories[i]->getTroops() << std::endl;
		player->printAdjacentCountries(territories[i]->adjacents);
		count++;
	}
	//sort the players lands from min armies to max in new vector territories
	std::sort(territories.begin(), territories.end(), comparisonFunction);

	int max = 0;
	int maxIndex = -1;
	int minIndex = -1;
	for(std::vector<Territory>::size_type i=0; i<territories.size(); i++){
		max = 0;
		for(std::vector<Territory>::size_type j=0; j<territories[i]->adjacents.size(); j++){
			if(territories[i]->adjacents[j]->getTroops() > max && territories[i]->adjacents[j]->getOwner() != NULL){
				if(territories[i]->adjacents[j]->getOwner()->getName() == player->getName() && territories[i]->adjacents[j]->getTroops() > 1){
					maxIndex = j;
					max = territories[i]->adjacents[j]->getTroops();
				}
			}
		}
		//break out of the loop if the max is found and its bigger than than 1 and set minIndex
		if(max > 1){
			minIndex = i;
			break;
		}
	}

	if(maxIndex == -1 || minIndex == -1){
		std::cout << "Benevolant Computer did not fortify" << std::endl;
		return;
	}

	std::cout << "Benevolant computer decided to move half the troops from " << territories[minIndex]->adjacents[maxIndex]->getName() <<
			" to " << territories[minIndex]->getName() << std::endl;

	int transferTroops = (territories[minIndex]->getTroops() + territories[minIndex]->adjacents[maxIndex]->getTroops()) / 2;

	//increment troops on territory chosen
	territories[minIndex]->incTroops(transferTroops);
	//decrement troops on max country
	territories[maxIndex]->adjacents[maxIndex]->setTroops(territories[minIndex]->adjacents[maxIndex]->getTroops() - transferTroops);

	std::cout << "Benevolant Computer Fortified " << territories[minIndex]->getName() << ", new total is " << territories[minIndex]->getTroops() << std::endl;

}

PlayerStrategies::~PlayerStrategies(){
}

