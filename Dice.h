#ifndef DICE_H_
#define DICE_H_

#include <set>
#include <vector>

using namespace std;

class Dice{
	public:
		Dice();
		Dice(int a);
		~Dice();
		void roll();
		void printValues();

	private:
		multiset<int> rolledValues = {};
		int counts[6] = {};
		double percentages[6] = {};

};
#endif /* DICE_H_ */
