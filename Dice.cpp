#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include "Dice.h"
#include <set>
#include <vector>

#define N_SIDES_DICE 6
#if false
#define printDEBUG
#endif
using namespace std;

Dice::Dice(){

	// Initialize seed for the random function
	int seed = time(0);
	#ifdef printDEBUG
	std::cout << "seed value is:\t" << seed << std::endl;
	#endif
	srand(seed);

	// Initialize array keeping track of instances of dice values
	counts = new int[N_SIDES_DICE];
	for(int i = 0; i < N_SIDES_DICE; i++) counts[i] = 0;

	// Initialize array keeping track of the percentage of values rolled
	percentages = new double[N_SIDES_DICE];

	// Initialize variable to keep track of how many rolls there have been so far
	n = new int[1];
	n[0] = 0;
}


Dice::~Dice(){
	// Delete pointers
	delete[] counts;
	delete[] percentages;
	delete[] n;
}


void Dice::activate(int* return_values){

	// Initialize array to 0
	for(int i = 0; i < 3; i++) return_values[i] = 0;

	int a;

	// Ask user for input
	std::cout<<"How many dice to roll?\t";
	std::cin>> a;

	// Roll dice
	roll(a,return_values);
}

// Roll dice
void Dice::roll(int a, int* b) {

    for(int i  = 0; i < a; i++){
        n[0]++; // Increment roll counter

        int r = 1 + (rand() % N_SIDES_DICE); // Generate random number
        b[i] = r; // Store random number

        #ifdef printDEBUG
        cout << "r: " << r << endl;
        #endif
        ++counts[r-1]; // Increment array of counts
    }
    
    //Hardcoded Sort
    int temp;
    if(b[0] < b[1]){
        temp = b[0];
        b[0] = b[1];
        b[1] = temp;
    }
    if(b[1] < b[2]){
        temp = b[1];
        b[1] = b[2];
        b[2] = temp;
    }
    if(b[0] < b[1]){
        temp = b[0];
        b[0] = b[1];
        b[1] = temp;
    } 
	
    // Calculate percentage of each dice value up to this point
    for(int i = 0; i < N_SIDES_DICE; i++){
            percentages[i] = counts[i] / (double) (n[0]);
    }
}

// Print the percentage array
void Dice::printAverages(){
    std::cout<<"Percentages of Spins:\n";
    for(int i=0; i <N_SIDES_DICE; i++) std::cout<<"\t"<<(i+1)<<": "<<percentages[i]*100<<"%\n";
}

// Getter for the count array
int Dice::getCount(int a){
    return counts[a+1];
}
