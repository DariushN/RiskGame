#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include "Dice.h"


using namespace std;

// Driver
int main() {

	// 2 dice "facility" objects?

	int numDice = 0;

	cout << "How many dice do you want to roll? (1-3)" << endl;
	cin >> numDice;

	Dice* d1 = new Dice(numDice);

	delete d1;

	return 0;

}



