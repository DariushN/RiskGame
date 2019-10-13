#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include "Dice.h"


using namespace std;

// Driver
int main() {

	// 2 Dice facility objects
	Dice* d1 = new Dice();
	Dice* d2 = new Dice();

	int a[3];
	for(int i = 0; i < 10; i++){
		d2->activate(a); // Test the function that asks for user input
	}

	for(long i = 0; i < 100000; i++){
		d1->roll(3,a); // Test roll function
		cout<< a[0] <<"\t" << a[1] <<"\t" <<a[2] <<"\n";
	}
	d1->printAverages();
	d2->printAverages();

	// Delete Dice objects
	delete d1;
	delete d2;
	return 0;

}

