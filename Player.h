
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector> 
#include "Dice.h"
class Territory;


class Player {
public:
    Player();
    virtual ~Player();
    int getId();
    void setId(int a);
    std::string getName();
    void setName(std::string a);
    std::vector <Territory*> lands;
	void reinforce();
	void attack();
	void fortify();
	//Needs a hand of Risk cards 
	Dice* dice;
private:
    int* id;
    std::string* name;
};

#endif /* PLAYER_H */

