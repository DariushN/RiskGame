#ifndef DICE_H_
#define DICE_H_

#include <set>
#include <vector>

using namespace std;

class Dice{
	public:
		Dice();
		//Dice(int a);
		~Dice();
		void roll(int n, int* container);
		void printValues();
		void activate(int* return_values);
                void printAverages();
                int getCount(int a);
	private:
		//multiset<int> rolledValues = {};
		int* counts;
		double* percentages;
		int * n;
};
#endif /* DICE_H_ */