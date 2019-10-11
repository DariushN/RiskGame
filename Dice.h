#ifndef DICE_H_
#define DICE_H_

#include <set>
#include <vector>

using namespace std;

class Dice{
	public:
		Dice(); // Default constructor
		~Dice(); // Destructor
		void roll(int n, int* container); // Roll dice
		void activate(int* return_values); // Initiate turn
		void printAverages(); // Print percentages array
		int getCount(int a); // Getter for the count array
	private:
		int* counts; // Array keeping track of instances of dice values
		double* percentages; // Array keeping track of the percentage of values rolled so far
		int * n; // Int keeping track of how many dice rolls there have been so far
};
#endif /* DICE_H_ */
