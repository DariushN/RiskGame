#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include "Dice.h"


using namespace std;

// Driver
int main() {


	//int numDice = 0;

	/*cout << "How many dice do you want to roll? (1-3)" << endl;
	cin >> numDice;*/

	Dice* d1 = new Dice();
	Dice* d2 = new Dice();
	int a[3];
	for(int i = 0; i < 10; i++){
		d2->activate(a);
	}
	for(long i = 0; i < 100000; i++){
		d1->roll(3,a);
		cout<< a[0] <<"\t" << a[1] <<"\t" <<a[2] <<"\n";
	}
	d1->printAverages();
	d2->printAverages();
	//for(int i = 0; i < 3; i++) std::cout<<a[i] <<"\t";
	delete d1;
	delete d2;
	return 0;

}