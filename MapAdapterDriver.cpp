#include <cstdlib>
#include <iostream>
#include "MapLoader.h"
using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::cerr;
using std::vector;
using std::to_string;

int main(int argc, char** argv) {
    MapLoader* a;
    a = new ConquestAdapter();
    Map* MAP = a->MapBuilder("Domination_maps/Earth Alternate.map");
    if(! MAP->isValid()){//Check if map is valid.
        std::cerr<<"Map is not valid!\n";
        return 1;
    }
	//Print out map data
    std::cout<<"Map name: " << MAP->getName() << endl;
    std::cout<< "Map continents:"<<endl;
    for(auto&& x:MAP->Continents){
        std::cout<<"\t"<< x->getName() <<endl;
        for(auto&& y:x->Territories){
            std::cout<<"\t\t"<<(*y).getID()<<"\t"  <<(*y).getName() <<endl;
            for(auto&& z:y->adjacents){
                std::cout<<"\t\t\t\t"<<(*z).getName()<<endl;
            }
        }
    }
    return 0;
}

