#include "GameEngine.h"
#include <Windows.h>
#include <iostream>
#include <limits>
#include <iomanip>

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::cerr;
using std::vector;
using std::to_string;

template<typename T> void printElement(T t, const int& width){
	// Taken from https://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c
	// By user Cyril Leroux
	const char separator = ' ';
	cout << left << setw(width) << setfill(separator) << t;
}

// Default constructor
GameEngine::GameEngine() {
	MAP = nullptr;
	players = nullptr;
	deck = nullptr;
	turn = nullptr;
	N_players = 0;
	phase = new std::string("");
}

// Parametrized constructor
GameEngine::GameEngine(Map* m, Player* p, int n){
	MAP = m;
	players = p;
	N_players = n;
	turn = p;
	phase = new std::string("");
}

// Copy constructor
GameEngine::GameEngine(const GameEngine& orig) {
	players = new Player(*orig.players);
	deck = new Deck(*orig.deck);
	MAP = new Map(*orig.MAP);
	turn = new Player(*orig.turn);
	phase = new std::string(*orig.phase);
}

// Assignment operator
GameEngine& GameEngine::operator=(const GameEngine &orig) {
	players = orig.players;
	deck = orig.deck;
	MAP = orig.MAP;
	turn = orig.turn;
	phase = orig.phase;
	if (&orig==this){
		delete players;
		delete deck;
		delete MAP;
		delete turn;
		delete phase;
		players = new Player(*orig.players);
		deck = new Deck(*orig.deck);
		MAP = new Map(*orig.MAP);
		turn = new Player(*orig.turn);
		phase = new std::string(*orig.phase);
	}
	return *this;
}

// Destructor
GameEngine::~GameEngine() {
	if(MAP != nullptr) delete MAP;
	if(players != nullptr) delete[] players;
	if(deck != nullptr) delete deck;
	if(turn != nullptr) delete turn;
	if(phase != nullptr) delete phase;
}

void GameEngine::Setup(){
	if(MAP==nullptr || !(MAP->isValid())){//Check if map is initialized
		SelectMaps();
	}
	string temp;
	deck = new Deck(MAP->Territories);//initialize deck
	N_players = 7;
	// Ask user to enter the number of players and validate
	while(N_players < 2 || N_players > 6){
		cout<<"Enter number of players (2-6): ";
		cin>>N_players;
		while(std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Please Enter a number: ";
			std::cin >> N_players;
		}
	}

	int A;// Number of armies
	switch(N_players){
	case 2:
		A = 40;
		break;
	case 3:
		A = 35;
		break;
	case 4:
		A = 30;
		break;
	case 5:
		A = 25;
		break;
	case 6:
		A = 20;
		break;
	default:
		cerr<<"Error, invalid number of players.";
		exit(1);
	}
	players = new Player[N_players];
	// Set each player's name, ID, and number of armies
	for(int i = 0; i < N_players; i++){
		players[i].setId(i);
		cout<<"What is player #"<<i<<"'s name? ";
		cin>>temp;
		while(std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Please Enter a number: ";
			std::cin >> temp;
		}
		players[i].setName(temp);
		players[i].setArmies(A);
	}
	int n = 0;
	// In a round-robin manner, assign a territory to a player
	for(auto&& x:MAP->Territories){
		players[n%N_players].lands.push_back(x);
		x->setOwner(&players[n%N_players]);
		n++;
	}
	// In a round-robin manner, assign each player's armies
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
	bool keepUserTrapped = true; // Boolean to ensure valid user input
	while(keepUserTrapped){
		cout<<"The following maps are available:\n";
		int n = 0;
		// Print directory of maps
		for(auto&& x:names){
			cout<<"\t"<<to_string(n++)<<"\t"<<x<<endl;
		}
		int user_choice = n+1;
		while(user_choice <0 || user_choice >n){
			cout<<"Enter index of desired map (0-" << to_string(n-1)<<") or "<<to_string(n) << " to enter your own: ";
			cin>>user_choice;
			while(std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Please Enter a number: ";
				std::cin >> user_choice;
			}
		}
		string filename;
		// Allow user to enter their own path if desired
		if(user_choice == n){
			cout<<"please enter desired map file with path (if in other directory): "<<endl;
			cin>>filename;
		}else{
			filename = "Maps/" + names.at(user_choice);
		}
		MapLoader* mapLoader = new MapLoader();
		MAP = mapLoader->MapBuilder(filename);
		keepUserTrapped = !(MAP->isValid());
		// Error message if chosen file was invalid
		if(keepUserTrapped){
			delete MAP;
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
	int a;
	// While the game is not won, allow each player to make a move
	while(!isWinner){
		// When all countries are owned by a player, the game is won
		for(int i = 0; i < this->N_players; i++){
			turn = &players[i]; // Set turn

			// Determine if the player has won
			if(players[i].lands.size() == this->MAP->Territories.size()) {
				Notify(); // Display final stats and a celebratory message
				isWinner = true;
				break;
			}
			else if(players[i].lands.size() == 0){ // If the player lost, print a message and display final stats
				cout << "\n\t---" << players[i].getName() << " has no more lands and is out of the game!---" << endl;
				Notify();
			}

			std::cout <<"\n\n" << players[i].getName() << "'s turn" << std::endl;
			Notify(); // Display stats

			this->setPhase(" Reinforcement"); // Set phase
			players[i].reinforce(this->MAP);

			this->setPhase(" Attack");
			players[i].attack(this->MAP);

			this->setPhase(" Fortification");
			players[i].fortify();

			// For brevity's sake (demonstration purposes)
			cout << "Enter -1 to end the game, 0 to declare the first player the winner, or any other number to continue: ";
			cin >> a;

			if (a == -1) { // End the game
				cout << "\nThanks for playing!" << endl;
				return;
			}
			else if(a == 0){ // Declare the first player as the winner and exit game

				int s = players[1].lands.size();
				cout << "\n\t---" << players[0].getName() << " is conquering " << players[1].getName() << "'s territories!---" << endl;

				// Give all of player 2's territories to player 1
				for(int i = 0; i < s; i++){
					Territory* a = players[1].lands.back();
					players[1].lands.pop_back();
					players[0].lands.push_back(a);

					cout << "\n\t---" << a->getName() << " has been conquered---" << endl;

					// Display that player 2 has been eliminated
					if(players[1].lands.size() == 0){
						cout << "\n\t---" << players[1].getName() << " has been eliminated---" << endl;
					}

					// Update the view to reflect the changes in territory
					Notify();
				}
				exit(1);
			}
			else{ // Otherwise continue the game
				continue;
			}

		}
	}
}

void GameEngine::mainGameLoop(Map* MAP, std::vector<Player*> players){
	bool isWinner = false;
	int a;

	// While the game is not won, allow each player to make a move
	while(!isWinner){
		for(int i = 0; i < players.size(); i++){
			turn = players[i];
			// When all countries are owned by a player, the game is won
			if(players[i]->lands.size() == MAP->Territories.size()) {
				std::cout << "The Winner is " << players[i]->getName() << std::endl;
				isWinner = true;
				break;
			}

			players[i]->reinforce(MAP);
			players[i]->attack(MAP);
			players[i]->fortify();
			cout << "Enter -1 if you want to end the game (or any key to continue): ";
			cin >> a;
			if (a == -1) {
				cout << "\nThanks for playing!" << endl;
				return;
			}
			else {
				continue;
			}
		}
	}
}

// Helper method to print territories
void GameEngine::printTerritories(){
	for(auto&& x:MAP->Territories) cout<<x->toString();
}

void GameEngine::begin(){

	// Initialize variables

	int n_maps = 0;
	int n_players = 0;
	vector<Map*> maps;
	int n_games = 0;
	int max_rounds;
	string* winner_names;
	char a = 0;

	// Attach observer
	StatsObserver S(&(*this));

	// Start game

	cout<<"Beginning Risk Game!"<<endl;

	while(a!= '0' && a != '1'){
		cout<<"Please enter 0 for default multiplayer mode, or 1 for tournament mode:\n\t";
		cin>>a;
	}
	if(a == '0'){
		Setup();
		mainGameLoop();
	}else if(a =='1'){ // Enter tournament mode
		a = 0;
		// Get number of maps
		while( a < '1' || a >'5'){
			cout<<"How many maps will be used (1-5)?"<<endl<<"\t";
			cin>>a;
		}

		n_maps = a - '0';
		vector<string> names = get_all_files_names_within_folder("Maps");
		for(int i = 0; i < n_maps; i++){
			bool keepUserTrapped = true; // Boolean to ensure valid user input
			while(keepUserTrapped){
				cout<<"The following maps are available:\n";
				int n = 0;
				// Print directory of maps
				for(auto&& x:names){
					cout<<"\t"<<to_string(n++)<<"\t"<<x<<endl;
				}
				int user_choice = n+1;
				while(user_choice <0 || user_choice >n){
					cout<<"Enter index of desired map (0-" << to_string(n-1)<<") or "<<to_string(n) << " to enter your own: ";
					cin>>user_choice;
					while(std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore();
						std::cout << "Please Enter a number: ";
						std::cin >> user_choice;
					}
				}
				string filename;
				// Allow user to enter their own path if desired
				if(user_choice == n){
					cout<<"please enter desired map file with path (if in other directory): "<<endl;
					cin>>filename;
				}else{
					filename = "Maps/" + names.at(user_choice);
				}
				MapLoader* mapLoader = new MapLoader();
				MAP = mapLoader->MapBuilder(filename);
				keepUserTrapped = !(MAP->isValid());
				// Error message if chosen file was invalid
				if(keepUserTrapped){
					delete MAP;
					cout<<"Map file chosen was invalid, please choose another."<<endl;
				}
			}
			cout<<"Map selected is: " <<MAP->getName()<<endl;
			maps.push_back(MAP);
		}
		a = 0;
		// Get number of players and strategies for them
		while(a < '2' || a > '4'){
			cout<<"Please select number of players in Tournament (2-4):\t";
			cin >>a;
		}

		n_players = a - '0';
		N_players = n_players;
		players = new Player[n_players];

		for(int i = 0; i < n_players; i++){
			GameObserver* G = new GameObserver(&players[i]);//Create and attach game observer

			cout<<"For player #"<<i<<", which strategy should be used?"<<endl;
			cout<<"\tOptions are:\n";
			cout<<"\t\t1.AggressiveComputer"<<endl;
			cout<<"\t\t2.BenevolentComputer"<<endl;
			cout<<"\t\t3.CheaterComputer"<<endl;
			cout<<"\t\t4.RandomComputer"<<endl;
			a = 0;
			while(a < '1' || a >'4'){
				cout<<"Please choose an option from 1-4:\t";
				cin>>a;
			}
			// Set players
			if(a=='1'){
				players[i].setStrategy(new AggressiveComputer());
				players[i].setName("p"+to_string(i)+"_AC");
				players[i].setId(i);
			}else if(a=='2'){
				players[i].setStrategy(new BenevolentComputer());
				players[i].setName("p"+to_string(i)+"_BC");
				players[i].setId(i);
			}else if(a=='3'){
				players[i].setStrategy(new CheaterComputer());
				players[i].setName("p"+to_string(i)+"_CC");
				players[i].setId(i);
			}else if(a=='4'){
				players[i].setStrategy(new RandomComputer());
				players[i].setName("p"+to_string(i)+"_RC");
				players[i].setId(i);
			}
		}

		a = 0;
		// Get number of games
		while(a<'1' || a > '5'){
			cout<<"How many games should be played in each map (1-5)?"<<endl<<"\t";
			cin>>a;
		}
		n_games = a - '0';

		// Get number of rounds before it is considered a draw.
		max_rounds = 0;
		while(max_rounds < 3 || max_rounds > 50){
			cout<<"How many rounds per game before being declared a draw (3-50)?\t";
			cin>>max_rounds;
			while(std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Please Enter a number: ";
				std::cin >> max_rounds;
			}
		}


		winner_names = new string[n_games*n_maps];
		if(winner_names == nullptr){
			cerr<<"Error: insufficient memory for winner logs"<<endl;
			exit(42);
		}

		// Start tournament
		for(int i = 0; i < n_maps; i++){
			MAP = maps.at(i);
			cout<<"Map is: "<< MAP->getName()<<endl;
			for(int j = 0; j < n_games; j++){
				// Store the winner of each game
				winner_names[j + n_games*i] = TournamentGameLoop(MAP,players,max_rounds);
			}
		}

		// Display report at the end of the game

		cout<<"\nM: ";
		for(auto && x:maps) cout<<x->getName()<<",";
		cout<<"\b \b\n";

		cout<<"P: ";
		for(int i =0; i < n_players; i++) cout<<players[i].getStrategyName()<<",";
		cout<<"\b \b\n";

		cout<<"G: "<<n_games<<endl;
		cout<<"D: "<<max_rounds<<endl;
		cout<<"\n\n";

		// Print table of results
		printElement(" ",25);
		for(int i = 0; i < n_games; i++){
			printElement("Game"+to_string(i),10);
		}
		cout<<endl;
		for(int i = 0; i < n_maps; i++){
			printElement(maps.at(i)->getName(),25);
			for(int j = 0; j < n_games; j++){
				printElement(winner_names[j + n_games*i],10);
			}
			cout<<endl;
		}
	}
}

string GameEngine::TournamentGameLoop(Map* m, Player* p, int n_turnsMAX){

	// Setup round
	for(int i = 0; i < N_players; i++){ // Empty old territories
		while(!players[i].lands.empty()) players[i].lands.pop_back();
	}

	MAP = m;
	deck = new Deck(MAP->Territories); // Initialize deck

	int A = 0; // Number of armies
	switch(N_players){
	case 2:
		A = 40;
		break;
	case 3:
		A = 35;
		break;
	case 4:
		A = 30;
		break;
	default:
		cerr<<"Error, invalid number of players.";
		exit(1);
	}
	int n = 0;

	// Giving out territories
	for(auto&& x:MAP->Territories){
		players[n%N_players].lands.push_back(x);
		x->setOwner(&players[n%N_players]);
		n++;
	}

	// In a round-robin manner, assign each player's armies
	cout<<"Assigning Armies"<<endl;
	for(int i = 0; i <N_players; i++){
		players[i].setArmies(A);
		int nLands = players[i].lands.size();
		n = 0;
		while(players[i].getArmies() != 0){
			players[i].setArmies(players[i].getArmies()-1);
			players[i].lands.at(n%nLands)->incTroops();
			n++;
		}
	}


	// Begin game
	bool isWinner = false;
	int n_turns = 0;

	// While the game is not won, allow each player to make a move
	while(!isWinner){
		// When all countries are owned by a player, the game is won
		for(int i = 0; i < this->N_players; i++){
			turn = &players[i]; // Set turn
			// Determine if the player has won
			if(players[i].lands.size() == this->MAP->Territories.size()) {
				Notify(); // Display final stats and a celebratory message
				isWinner = true;
				return players[i].getName();
			}else if(players[i].lands.size() == 0){ // If the player lost, print a message and display final stats
				cout << "\n\t---" << players[i].getName() << " has no more lands and is out of the game!---" << endl;
				Notify();
				continue;
			}

			std::cout <<"\n\n" << players[i].getName() << "'s turn" << std::endl;
			Notify(); // Display stats

			this->setPhase(" Reinforcement"); // Set phase
			players[i].reinforce(this->MAP);

			this->setPhase(" Attack");
			players[i].attack(this->MAP);

			this->setPhase(" Fortification");
			players[i].fortify();
		}
		n_turns++;
		if(n_turns >= n_turnsMAX){
			return "Draw";
		}
	}
	return "";
}


