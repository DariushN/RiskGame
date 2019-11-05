/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameEngine.cpp
 * Author: t_filler
 * 
 * Created on November 3, 2019, 6:44 PM
 */

#include "GameEngine.h"
#include <Windows.h>
#include <iostream>
#include <limits>
using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::cerr;
using std::vector;
using std::to_string;

#define printDebug

GameEngine::GameEngine() {
    MAP = nullptr;
    players = nullptr;
    deck = nullptr;
}    

GameEngine::GameEngine(const GameEngine& orig) {

}

GameEngine::~GameEngine() {
    if(MAP != nullptr) delete MAP;
    if(players != nullptr) delete[] players;
    if(deck != nullptr) delete deck;
}

void GameEngine::Setup(){
    if(MAP==nullptr || !(MAP->isValid())){//Check if map is initialized
        SelectMaps();
    }
    string temp;
    deck = new Deck(MAP->Territories);//initialize deck
    N_players = 7;
    while(N_players < 2 || N_players > 6){
        cout<<"Enter number of players (2-6): ";
        cin>>N_players;
        while(std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
			std::cout << "Please Enter a number: ";
			std::cin >> N_players;
		}
    }
    
    int A;
    switch(N_players){
        case 2:
            A = 40;
            #ifdef printDebug 
            cout<<"A (number of troops) is: "<<A;
            #endif
            break;
        case 3:
            A = 35;
            #ifdef printDebug 
            cout<<"A (number of troops) is: "<<A;
            #endif
            break;
        case 4:
            A = 30;
            #ifdef printDebug 
            cout<<"A (number of troops) is: "<<A;
            #endif
            break;
        case 5:
            A = 25;
            #ifdef printDebug 
            cout<<"A (number of troops) is: "<<A;
            #endif
            break;
        case 6:
            A = 20;
            #ifdef printDebug 
            cout<<"A (number of troops) is: "<<A;
            #endif
            break;
        default:
            cerr<<"Error, invalid number of players.";
            exit(1);
    }
    players = new Player[N_players];
    for(int i = 0; i < N_players; i++){
        players[i].setId(i);
        cout<<"What is player #"<<i<<"'s name? ";
        cin>>temp;
        players[i].setName(temp);
        players[i].setArmies(A);
    }
    int n = 0;
    for(auto&& x:MAP->Territories){
        players[n%N_players].lands.push_back(x);
        x->setOwner(&players[n%N_players]);
        n++;
    }
    for(int i = 0; i <N_players; i++){
        int nLands = players[i].lands.size();
        n = 0;
        while(players[i].getArmies() != 0){
            players[i].setArmies(players[i].getArmies()-1);
            players[i].lands.at(n%nLands)->incTroops();
            n++;
        }
    }
}

void GameEngine::SelectMaps(){
    vector<string> names = get_all_files_names_within_folder("Maps");
    MapLoader ml;
    bool keepUserTrapped = true;
    while(keepUserTrapped){
        cout<<"The following maps are available:\n";
        int n = 0;
        for(auto&& x:names){
            cout<<"\t"<<to_string(n++)<<"\t"<<x<<endl;
        }

        int user_choice = n+1;
        while(user_choice <0 || user_choice >n){
            cout<<"Enter index of desired map (0-" << to_string(n-1)<<") or "<<to_string(n) << " to enter your own: ";
            cin>>user_choice;
            while(std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
				std::cout << "Please Enter a number: ";
				std::cin >> user_choice;
			}
        }
        string filename;
        if(user_choice == n){
            cout<<"please enter desired map file with path (if in other directory): "<<endl;
            cin>>filename;
        }else{
            filename = "Maps/" + names.at(user_choice);
        }
        MAP = ml.MapBuilder(filename);
        keepUserTrapped = false;
        if(keepUserTrapped){
            cout<<"Map file chosen was invalid, please choose another."<<endl;
        }
    }
    cout<<"Map selected is: " <<MAP->getName()<<endl;
}



vector<string> GameEngine::get_all_files_names_within_folder(string folder){
    //Taken from https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
    //By herohuyongtao
    vector<string> names;
    string search_path = folder + "/*.map";
    WIN32_FIND_DATA fd; 
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd); 
    if(hFind != INVALID_HANDLE_VALUE) { 
        do { 
            // read all (real) files in current folder
            // , delete '!' read other 2 default folder . and ..
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
                names.push_back(fd.cFileName);
            }
        }while(::FindNextFile(hFind, &fd)); 
        ::FindClose(hFind); 
    } 
    return names;
}

void GameEngine::mainGameLoop(){
	bool isWinner = false;

	while(!isWinner){
		for(int i = 0; i < this->N_players; i++){
			if(players[i].lands.size() == this->MAP->Territories.size()) {
				isWinner = true;
				std::cout << "The Winner is " << players[i].getName() << std::endl;
				break;
			}
			std::cout <<"\n\n" << players[i].getName() << "'s turn" << std::endl;
			players[i].reinforce(this->MAP);
			players[i].attack(this->MAP);
			players[i].fortify();
		}
	}
}

void GameEngine::mainGameLoop(Map* MAP, std::vector<Player*> players){
	bool isWinner = false;

	while(!isWinner){
		for(int i = 0; i < players.size(); i++){
			if(players[i]->lands.size() == MAP->Territories.size()) {
				std::cout << "The Winner is " << players[i]->getName() << std::endl;
				isWinner = true;
				break;
			}
			std::cout <<"\n\n" << players[i]->getName() << "'s turn" << std::endl;
			players[i]->reinforce(MAP);
			players[i]->attack(MAP);
			players[i]->fortify();
		}
	}
}

void GameEngine::printTerritories(){
    for(auto&& x:MAP->Territories) cout<<x->toString();
}

bool GameEngine::compliesWithA2Q2(){
    if(MAP==nullptr || players == nullptr || deck==nullptr){
        return false;
    }
    Player* owner;
    bool invalid;
    for(auto&& x:MAP->Territories){//Check if owners are all valid
        invalid = true;
        owner = x->getOwner();
        for(int i =0; i < N_players; i++){
            if(&players[i] == owner){
                invalid = false;
                break;
            }
        }
        if(invalid){
            cerr<<"Error!\nTerritory: "<<x->getName()<<" has an invalid owner!"<<endl;
            return false;
        }
    }
    for(int i = 0; i < N_players; i++){//Check if all players have correct lands
        for(auto&& x:players[i].lands){
            if(x->getOwner()!=&players[i]){
                cerr<<"Error! Player: "<<players[i].getName()<<" points to territory: "<<x->getName()<<endl;
                cerr<<"This territory is owned by someone else!\n";
                return false;
            }
        }
    }
    int A;
    switch(N_players){
        case 2:
            A = 40;
            #ifdef printDebug
            cout<<"A (number of troops) is: "<<A;
            #endif
            break;
        case 3:
            A = 35;
            #ifdef printDebug
            cout<<"A (number of troops) is: "<<A;
            #endif
            break;
        case 4:
            A = 30;
            #ifdef printDebug
            cout<<"A (number of troops) is: "<<A;
            #endif
            break;
        case 5:
            A = 25;
            #ifdef printDebug
            cout<<"A (number of troops) is: "<<A;
            #endif
            break;
        case 6:
            A = 20;
            #ifdef printDebug
            cout<<"A (number of troops) is: "<<A;
            #endif
            break;
        default:
            cerr<<"Error, invalid number of players.";
            return false;
    }

    for(int i = 0; i < N_players; i++){
        int troops = 0;
        for(auto&& x:players[i].lands){
            troops +=x->getTroops();
        }
        if(troops != A){
            cerr<<"Player: "<<players[i].getName()<< " has the wrong number of armies!\n";
            cerr<<"Player has "<<troops<<" troops, should have "<< A<<endl;
            return false;
        }
    }
    return true;
}
