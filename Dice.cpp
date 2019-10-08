#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include "Dice.h"
#include <set>
#include <vector>

#define N_SIDES_DICE 6
#define printDEBUG
using namespace std;

Dice::Dice(){
	int seed = time(0);
	#ifdef printDEBUG
	std::cout << "seed value is:\t" << seed << std::endl;
	#endif
	srand(seed);
	counts = new int[N_SIDES_DICE];
	for(int i = 0; i < N_SIDES_DICE; i++) counts[i] = 0;
	percentages = new double[N_SIDES_DICE];
	n = new int[1];
	n[0] = 0;
}


Dice::~Dice(){
	//cout << "The sorted results are: ";
	//printValues();
	//cout << " and the percentage of 4s is " << percentages[3] << endl;
	std::cout<<"\ncounts:\n";
	for(int i = 0; i < N_SIDES_DICE; i++) std::cout<<"\t"<<counts[i]<<std::endl;
	delete[] counts;
	delete[] percentages;
	delete[] n;
}

/*
void Dice::printValues() {
	int length = rolledValues.size();
	for (int i = 0; i < length; i++) {
		cout << *rolledValues.begin()+i << ", ";
	}
}*/

void Dice::activate(int* return_values){
	for(int i = 0; i < 3; i++) return_values[i] = 0;
	int a;
	std::cout<<"How many dice to roll?\t";
	std::cin>> a;
	roll(a,return_values);
}

void Dice::roll(int a, int* b) {

	
	for(int i  = 0; i < a; i++){
		n[0]++;
		int r = 1 + (rand() % N_SIDES_DICE); // Generate random number
		b[i] = r;
		#ifdef printDEBUG
		cout << "r: " << r << endl;
		#endif
		++counts[r-1];
		n[0]++;
		//rolledValues.insert(r); // Add rolled value to sorted container
	}
	//add hardcoded sort 
	
	// Calculate percentage and increment count array
	for(int i = 0; i < N_SIDES_DICE; i++){
		percentages[i] = counts[i] / (double) (n[0]);
	}

}