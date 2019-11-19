#include <iostream>
#include <iomanip>
#include <list>
#include "GameObserver.h"
#include "Player.h"
#include "GameEngine.h"

using namespace std;

// Observer class
Observer::Observer() {
}

Observer::~Observer() {
}

// GameObserver class (part 2)
GameObserver::GameObserver() {
	subject = new Player();
}

GameObserver::GameObserver(const GameObserver& orig) {
	subject = new Player(*orig.subject);
}


GameObserver::GameObserver(Player* p) {
	subject = p;
	subject->Attach(this);
}

GameObserver& GameObserver:: operator = (const GameObserver &g){
	subject = g.subject;
	return *this;
}

// Destructor
GameObserver::~GameObserver() {
	subject->Detach(this);
	delete subject;
}

void GameObserver::Update() {
	// Display what phase the player is in
	cout << "\n\n=============================================" << endl;
	cout << "--- Player " << subject->getName() << ": " << subject->getPhase() << " phase ---" << endl;
	cout << "=============================================\n\n" << endl;
}

// StatsObserver class (part 3)
StatsObserver::StatsObserver() {
	subject = new GameEngine();
}

StatsObserver::StatsObserver(const StatsObserver& orig) {
	subject = new GameEngine(*orig.subject);
}

StatsObserver::StatsObserver(GameEngine* p) {
	subject = p;
	subject->Attach(this);
}

StatsObserver& StatsObserver:: operator = (const StatsObserver &g){
	subject = g.subject;
	return *this;
}

// Destructor
StatsObserver::~StatsObserver() {
	subject->Detach(this);
	delete subject;
}

template<typename T> void StatsObserver::printElement(T t, const int& width){
	// Taken from https://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c
	// By user Cyril Leroux
	const char separator = ' ';
	cout << left << setw(width) << setfill(separator) << t;
}


void StatsObserver::Update() {

	double numCountries = subject->getMap()->Territories.size(); // Total number of countries on the map
	double numControlled = (subject->getPlayers()+0)->lands.size();
	double percentage;
	cout << fixed;
	cout << setprecision(2); // Set decimal places

	// Print celebratory message
	if(numControlled == numCountries){
		cout << "\n\t****************************************" << endl;
		cout << "\tCongratulations! The Winner is " << (subject->getPlayers()+0)->getName() << endl; // Display winner
		cout << "\tThanks for playing!" << endl;
		cout << "\t****************************************\n" << endl;
	}

	// Print table
	cout << "---Percentage of the world controlled by each player---\n" << endl;
	printElement("|   Player", 16);
	printElement("|",6);
	printElement("% of world  |", 20);
	cout << endl;
	printElement("-----------------------------------",0);
	cout << endl;


	for(int i = 0; i < subject->getNumPlayers(); i++){

		numControlled = (subject->getPlayers()+i)->lands.size(); // Number of countries controlled by the player
		if(numControlled == 0){
			continue;
		}
		percentage = (numControlled/numCountries)*100; // Calculate percentage

		printElement("|",5);
		printElement((subject->getPlayers()+i)->getName(), 11);
		printElement("|",5);
		printElement(percentage, 0);
		printElement("%",7);
		printElement("|",0);
		cout << endl;
	}

	printElement("-----------------------------------",0);
	cout << endl;

}

// Subject class

Subject::Subject() {
	observers = new list<Observer*>;
}

Subject::~Subject() {
	delete observers;
}

void Subject::Attach(Observer* o) {
	observers->push_back(o);
}

void Subject::Detach(Observer* o) {
	observers->remove(o);
}

void Subject::Notify() {
	list<Observer*>::iterator i = observers->begin();
	for (; i != observers->end(); ++i)
		(*i)->Update();
}




