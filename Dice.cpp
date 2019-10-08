#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include "Dice.h"
#include <set>
#include <vector>


using namespace std;

Dice::Dice(){
	roll();
}

Dice::Dice(int num){

	for(int i = 0; i < num; i++){
		roll(); // Roll die
	}

}

Dice::~Dice(){
	cout << "The sorted results are: ";
	printValues();
	cout << " and the percentage of 4s is " << percentages[3] << endl;
}


void Dice::printValues() {
	int length = rolledValues.size();
	for (int i = 0; i < length; i++) {
		cout << *rolledValues.begin()+i << ", ";
	}
}

void Dice::roll() {

	srand(time(NULL));
	int r = 1 + (rand() % 5); // Generate random number

	cout << "r: " << r << endl;
	rolledValues.insert(r); // Add rolled value to sorted container


	// Calculate percentage and increment count array
	percentages[r-1] = (++counts[r-1]/(double)rolledValues.size());


}








