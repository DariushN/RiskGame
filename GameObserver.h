#pragma once

// Forward declarations
class Player;
class GameEngine;

class Observer {
public:
	~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};

// GameObserver class (part 2)
class GameObserver : public Observer {

	public:
		GameObserver(); // Default constructor
		GameObserver(const GameObserver& GO); // Copy constructor
		GameObserver(Player* p); // Parametrized constructor taking a Player object
		GameObserver& operator = (const GameObserver &g); // Assignment operator overloading
		~GameObserver(); // Destructor
		void Update(); // Update method
	private:
		Player* subject; // Player subject

};

// StatsObserver class (part 3)
class StatsObserver : public Observer{

	public:
		StatsObserver(); // Default constructor
		StatsObserver(const StatsObserver& SO); // Copy constructor
		StatsObserver(GameEngine* p); // Parametrized constructor taking a GameEngine object
		StatsObserver& operator = (const StatsObserver &s); // Assignment operator overloading
		~StatsObserver(); // Destructor
		void Update(); // Update method
		template<typename T> void printElement(T t, const int& width); // Helper method to print a table
	private:
		GameEngine* subject; // GameEngine subject

};

#pragma once
#include <list>
using namespace std;

class Observer;

class Subject {
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	Subject();
	~Subject();
private:
	list<Observer*>* observers;
};

