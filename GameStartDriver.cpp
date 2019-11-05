#include <cstdlib>
#include <iostream>
#include "GameEngine.h"
using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::cerr;
using std::vector;
using std::to_string;


int main(int argc, char** argv) {
    GameEngine GE;
    GE.SelectMaps();
    GE.Setup();
    GE.printTerritories();
    return 0;
}

