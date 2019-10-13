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


int main(int argc, char** argv) {
//int main2(int argc, char** argv) {
    std::cout<<"Beginning program"<<endl;
    //Map MAP = MapBuilder("Maps/lotr_invalid.map");//test if map is not connected
    Map MAP = MapBuilder("Maps/risk.map");//test with proper case
    //Map MAP = MapBuilder("Maps/risk.png");//test how it handles random files
    if(! MAP.isValid()){
        std::cerr<<"Map is not valid!\n";
        return 1;
    }
    std::cout<<"Map name: " << MAP.getName() << endl;
    std::cout<< "Map continents:"<<endl;
    for(auto&& x:MAP.Continents){
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

