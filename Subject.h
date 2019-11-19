#pragma once
#include "GameObserver.h"
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
