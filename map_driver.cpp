/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   map_driver.cpp
 * Author: Tzvi Filler
 *
 * Created on October 11, 2019, 3:50 PM
 */

#include <cstdlib>
#include <iostream>
#include "Map.h"
#include "Territory.h"
#include "Continent.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Territory a1,a2,a3;a1.setName("a1");a2.setName("a2");a3.setName("a3");
    Territory b1,b2,b3;b1.setName("b1");b2.setName("b2");b3.setName("b3");
    Territory c;c.setName("c");
    Continent A,B;A.setName("A");B.setName("B");
    
    a1.setLocation(&A);A.Territories.push_back(&a1);
    a2.setLocation(&A);A.Territories.push_back(&a2);
    a3.setLocation(&A);A.Territories.push_back(&a3);
    a1.addAdj(&a2);
    a1.addAdj(&a3);
    a2.addAdj(&a1);
    a3.addAdj(&a2);
    
    b1.setLocation(&B);B.Territories.push_back(&b1);
    b2.setLocation(&B);B.Territories.push_back(&b2);
    b3.setLocation(&B);B.Territories.push_back(&b3);
    b1.addAdj(&b2);
    b1.addAdj(&b3);
    b2.addAdj(&b1);
    b3.addAdj(&b2);
    
    b3.addAdj(&a1);
    a1.addAdj(&b3);
    
    Map map1;
    map1.Territories.push_back(&a1);
    map1.Territories.push_back(&a2);
    map1.Territories.push_back(&a3);
    map1.Territories.push_back(&b1);
    map1.Territories.push_back(&b2);
    map1.Territories.push_back(&b3);
    map1.Continents.push_back(&A);
    map1.Continents.push_back(&B);

    Map map2;
    map2.Territories.push_back(&a1);
    map2.Territories.push_back(&a2);
    map2.Territories.push_back(&a3);
    map2.Territories.push_back(&b1);
    map2.Territories.push_back(&b2);
    map2.Territories.push_back(&b3);
    map2.Territories.push_back(&c);//Invalid
    map2.Continents.push_back(&A);
    map2.Continents.push_back(&B);    
    
    
    if(map1.isValid()){
        std::cout<<"map1 is valid"<<std::endl;
    }else{
        std::cout<<"map1 is not valid"<<std::endl;
    }
    
    if(map2.isValid()){
        std::cout<<"map2 is valid"<<std::endl;
    }else{
        std::cout<<"map2 is not valid"<<std::endl;
    }
    
    a3.adjacents.pop_back();
    if(map1.isValid()){
        std::cout<<"map1 is still valid"<<std::endl;
    }else{
        std::cout<<"map1 is no longer valid"<<std::endl;
    }
    
    return 0;
}

