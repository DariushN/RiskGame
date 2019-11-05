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
    if(GE.compliesWithA2Q2()){
        cout<<"Game complies with rules as laid out in the requirements of part #2!"<<endl;
    }else{
        cout<<"Game does not comply with rules as laid out in the requirements of part #2!"<<endl;
    }
    return 0;
}

