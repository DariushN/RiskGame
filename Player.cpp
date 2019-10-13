#include "Player.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>

Player::Player() {
	name = new std::string("");
	id = new int(1);
	dice = new Dice();
	armies = new int(0);
	hand = new Hand();
}

std::string Player::getName(){
    return *name;
}

void Player::setName(std::string Name) {
	*name = Name;
}

void Player::setId(int iD) {
	*id = iD;
}

int Player::getArmies() {
	return *armies;
}

void Player::setArmies(int Armies){
	*armies = Armies;
}

int Player::getId(){
    return *id;
}

void Player::attack() {
	std::cout << "Attacking" << std::endl;
}

void Player::fortify() {
	std::cout << "fortifying" << std::endl;
	bool deciding = true;
	bool fortifying = true;

	while(deciding) {
		int count = 1;
		//print out all players territories and number of armies on each
		for(std::vector<Territory>::size_type i = 0; i != this->lands.size(); i++) {
			std::cout << count << ": " <<  this->lands[i]->getName() << "     Armies: " << this->lands[i]->getTroops() << std::endl;
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
			for(std::vector<Territory>::size_type i = 0; i != this->lands.size(); i++) {
				std::cout << count << ": " <<  this->lands[i]->getName() << "  Armies: " <<
						this->lands[i]->getTroops() << std::endl;
				this->printAdjacentCountries(this->lands[i]->adjacents);
				count++;
			}

		while(fortifying) {
			std::cout << "Enter the country number you would like to move your armies from or type -1 to end fortification"  << std::endl;
			int country1;
			cin >> country1;

			if(country1 == -1) break;

			std::cout << "Enter the country you would like to fortify or type -1 to end fortification" << std::endl;
			int country2;
			std::cin >> country2;
			if(country2 == -1) break;

			//validation on countries picked
			if(country1 > count) {
				std::cout << "Please pick a valid starting country" << std::endl;
				continue;
			} else if(country2 > count) {
				std::cout << "Please pick a valid country to fortify" << std::endl;
				continue;
			} else if(this->lands[country1 - 1]->getTroops() <= 1) {
				std::cout << "Starting country must have more than 1 army, please pick another country" << std::endl;
				continue;
			} else if(!this->lands[country1 - 1]->isAdj(this->lands[country2 - 1])) {
				std::cout << "please pick countries that are adjacent" << std::endl;
			}

			//loop to get number of troops that user wants to move
			while(1) {
				std::cout << "how many troops would you like to move from " << this->lands[country1 - 1]->getName()
						<< " to " << this->lands[country2 - 1]->getName() << std::endl;

				int troops;
				cin >> troops;

				if(troops > this->lands[country1 - 1]->getTroops() - 1) { //must leave at least 1 troop on the territory
					std::cout << "Please pick a number less than "<< this->lands[country1 - 1]->getTroops() << std::endl;
					continue;
				}else {
					//increment troops on territory chosen
					this->lands[country2 - 1]->incTroops(troops);
					std::cout << "Fortified " << this->lands[country2 - 1]->getName() << ", new total is " << this->lands[country2 - 1]->getTroops() << std::endl;
					break;
				}
			}
			break;
		}
		break;
	}

	std::cout << "Fortification done" << std::endl;
}

void Player::printAdjacentCountries(std::vector<Territory*> territories) {
	//prints adjacent territories for each territory in vector
	std::cout << "Adjacent Countries: ";
	for(std::vector<Territory>::size_type i = 0; i != territories.size(); i++) {
		std::cout << territories[i]->getName() << "  ";
	}
	std::cout << "\n\n";
}

void Player::reinforce(Map* map) {
	std::cout << "Reinforcing" << std::endl;

	//check if user owns a continent
	int controlledContinents;
	if(this->continents.size() < 1){
		controlledContinents = 0;
	} else {
		for(std::vector<Continent>::size_type i = 0; i != this->continents.size(); i++) {
			controlledContinents += this->continents[i]->getValue();
		}
	}

	std::cout << "Number of armies from controlled continents: " << controlledContinents << std::endl;

	// get number of armies from countries
	int controlledCountries;
	if(this->lands.size() < 9) {
		controlledCountries = 3;
	} else {
		controlledCountries = floor(this->lands.size() / 3);
	}

	std::cout << "Number of armies from Controlled Countries: "<< controlledCountries << std::endl;

	int exchangeValue = this->hand->exchange(this->lands);
	std::cout << "Number of armies from Exchanged Cards: " << exchangeValue << std::endl;

	int totalArmies = controlledCountries + controlledContinents + exchangeValue; //add armies from exchange()
	this->setArmies(totalArmies);
	this->placeArmies(totalArmies);

	std::cout << "Done Reinforcing" << std::endl;
}

void Player::placeArmies(int armies) {
	bool decidingCountry = true;
	bool placingArmy = true;
	if(this->lands.size() > 0) {
		while(decidingCountry){
			//initial
			if (this->getArmies() < 1) {
				break;
			}
			std::cout << "Listing your countries, please select a country to place troops on, you have " << this->getArmies() << " troops to place." << std::endl;
			int count = 0;
			for(std::vector<Territory>::size_type i = 0; i != this->lands.size(); i++) {
				count++;
				std::cout << count << ": " <<  this->lands[i]->getName() << "  Armies: " << this->lands[i]->getTroops() << std::endl;
			}

			std::cout << "Enter the number of the country you wish to select" << std::endl;
			int number;

			cin >> number;

			if (number > count) {
				std::cout << "Please choose a valid country number from list" << std::endl;
				number = -1;
				continue;
			}

			while(placingArmy){
				std::cout << "Initial Armies on "+ this->lands[number - 1]->getName() + " are " << this->lands[number - 1]->getTroops() << std::endl;
				std::cout << "Enter amount of armies you would like to place, max amount you can place is " << this->getArmies() << std::endl; //maybe allow user to back out if they change their mind
				int armies;
				std::cin >> armies;

				if (armies > this->getArmies()) {
					std::cout << "You cannot place this many armies" << std::endl;
					continue;
				}
				//incremment troops and setArmies for player
				this->lands[number - 1]->incTroops(armies);
				std::cout << "new total on " << this->lands[number - 1]->getName() << " is " << this->lands[number - 1]->getTroops() << std::endl;
				int totalArmies = this->getArmies();
				this->setArmies(totalArmies - armies);
				break;
			}
		}
	}
}

Player::~Player() {
	delete name;
	delete id;
	delete dice;
	delete armies;
}

