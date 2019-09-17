/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: t_filler
 *
 * Created on September 4, 2019, 8:37 PM
 */

#include <cstdlib>
#include <iostream>
#include "Map.h"
#include "Player.h"
#include "Territory.h"
#include "Continent.h"
#include "MapLoaderUtility.h"
#include <sstream>
using namespace std;

/*
 * 
 */
bool debug = false;
int main(int argc, char** argv) {
    std::cout<<"Begining program"<<endl;
    Map MAP = MapBuilder("Maps/risk.map");
    std::cout<<"Map name: " << MAP.getName() << endl;
    std::cout<< "Map continents:"<<endl;
    for(auto&& x:MAP.Continents){
        std::cout<<"\t"<< x->getName() <<endl;
        for(auto&& y:x->Territories){
            //Territory TempTerritroy = *y;
            std::cout<<"\t\t"<<(*y).getID()<<"\t"  <<(*y).getName() <<endl;
            //std::cout<<"\t\t\t Adjacents:"<<endl;
            for(auto&& z:y->adjacents){
                std::cout<<"\t\t\t\t"<<(*z).getName()<<endl;
            }
        }
    }
    return 0;
}

