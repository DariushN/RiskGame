#include "Player.h"
#include "PlayerStrategies.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <limits>


//default constructor
Player::Player() {
	name = new std::string("");
	id = new int(1);
	dice = new Dice();
	armies = new int(0);
	hand = new Hand();
	phase = new std::string("");
	strategy = new HumanPlayer();
}

Player::Player(const Player &orig) {
    name = new string(*orig.name);
    id = new int(*orig.id);
    dice = new Dice(*orig.dice);
    armies = new int(*orig.armies);
    hand = new Hand(*orig.hand);
	phase = new std::string(*orig.phase);
	strategy = new HumanPlayer();
}

Player& Player::operator=(const Player &orig) {
    if(&orig!=this){
        delete name;
        delete id;
        delete dice;
        delete armies;
        delete hand;
        delete phase;
        delete strategy;
        name = new string(*orig.name);
        id = new int(*orig.id);
        dice = new Dice(*orig.dice);
        armies = new int(*orig.armies);
        hand = new Hand(*orig.hand);
        phase = new std::string(*orig.phase);
        strategy = new HumanPlayer();
    }
    return *this;
}

std::string Player::getPhase() {
	return *phase;
}

void Player::setPhase(std::string p) {
	*phase = p;
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

Hand* Player::getHand(){
	return hand;
}

Dice* Player::getDice(){
	return dice;
}


void Player::printAdjacentCountries(std::vector<Territory*> territories) {
	//prints adjacent territories for each territory in vector
	std::cout << "Adjacent Countries: ";
	for(std::vector<Territory>::size_type i = 0; i != territories.size(); i++) {
		//only display countries owned by player
		if(territories[i]->getOwner() == NULL){
			continue;
		}
		if(territories[i]->getOwner()->getName() == *this->name){
			std::cout << territories[i]->getName() << " ";
		}
	}
	std::cout << "\n\n";
}

void Player::recuperateArmies(Map* map){
	cout << "\t---Recuperating armies---" << endl;
	//check if user owns a continent
	this->hasContinent(map);
	int controlledContinents = 0;
	if(this->continents.size() > 0){
		for(std::vector<Continent>::size_type i = 0; i < this->continents.size(); i++) {
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
	std::cout << "Number of armies from Exchanged Cards: " << exchangeValue << endl;

	int totalArmies = controlledCountries + controlledContinents + exchangeValue; //add armies from exchange()
	this->setArmies(totalArmies);
}

void Player::placeArmies(int armies) {
	cout << "\n\t---Placing armies---" << endl;
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
			while(std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
				std::cout << "Please Enter a number: ";
				std::cin >> number;
			}

			if (number > count || number < 1) {
				std::cout << "Please choose a valid country number from list" << std::endl;
				number = -1;
				continue;
			}

			while(placingArmy){
				std::cout << "Initial Armies on "+ this->lands[number - 1]->getName() + " are " << this->lands[number - 1]->getTroops() << std::endl;
				std::cout << "Enter amount of armies you would like to place, max amount you can place is " << this->getArmies() << std::endl; //maybe allow user to back out if they change their mind
				int armies;
				std::cin >> armies;
				while(std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
					std::cout << "Please Enter a number: ";
					std::cin >> armies;
				}

				if (armies > this->getArmies() || armies < 1) {
					std::cout << "You cannot place this many armies" << std::endl;
					continue;
				}
				//increment troops and setArmies for player
				this->lands[number - 1]->incTroops(armies);
				std::cout << "\t---New total on " << this->lands[number - 1]->getName() << ": " << this->lands[number - 1]->getTroops() << "---" << std::endl;
				int totalArmies = this->getArmies();
				this->setArmies(totalArmies - armies);
				break;
			}
		}
	}
}

void Player::hasContinent(Map* map){
	std::vector<Territory>::size_type counter = 0;
	vector<Continent*> continents;
	continents = map->Continents;

	for(std::vector<Continent>::size_type i = 0; i< continents.size(); i++)
	{
		for(std::vector<Territory>::size_type k=0; k<this->lands.size(); k++)
		{
			if(continents[i]->getName() == this->lands[k]->location->getName())
			{
				counter += 1;
				if(counter == continents[i]->Territories.size())
				{
					//check if continent is already owned by player
					if (std::find(this->continents.begin(), this->continents.end(), continents[i]) != this->continents.end())
					{
						return;
					}
					this->continents.push_back(continents[i]);
				}
			}
		}
		counter = 0;
	}
}

Player::~Player() {
	delete name;
	delete id;
	delete dice;
	delete armies;
	delete hand;
	delete strategy;
	delete phase;
}

string Player::getStrategyName(){
    return strategy->getName();
}