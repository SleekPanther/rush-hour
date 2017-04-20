#include "Game.h"

Game::Game() {
	//Empty Board is already set up
	retrieveVehicles(board);
}

Game::~Game() {
}

vector<Vehicle> Game::getVehicles()
{
	return vector<Vehicle>();
}

void Game::load(){
	string progressFilename = "progress.txt";
	//vector<int> fileContents = GameSetup::readFile(progressFilename);
}

void Game::save(){

}

void Game::populateBoard(vector<int> fileContents){

}

void Game::retrieveVehicles(Board theBoard)
{//Hard coded values used for testing, these values will be retrived from the set up file via a gameSetup member function
	int numOfVehicles = 3;

	//Each of the groups of six/eight values below represent all of the info required to set up vehicles.  
	int sizeOfVOne = 2;
	bool vOneIsVertical = false;
	int xCoord1VOne = 1;
	int yCoord1VOne = 3;
	int xCoord2VOne = 2;
	int yCoord2VOne = 3;
	Coordinate2D v1FirstCoord(xCoord1VOne, yCoord1VOne);
	Coordinate2D v1SecondCoord(xCoord2VOne, yCoord2VOne);
	vector<Coordinate2D> vectOfCoords;
	vectOfCoords.push_back(v1FirstCoord);
	vectOfCoords.push_back(v1SecondCoord);
	//Now create this special vehicle passing first a board and second a vector of coordinates
	SpecialVehicle special(theBoard, vectOfCoords);
	//Create a pointer to this vehicle
	Vehicle * specialPoint = &special;
	//Add this pointer to the array of pointers
	vectorOfVehicles.push_back(specialPoint);
	//Test to see if we are able to call member functions on this vehicle via the vector of pointers
	cout << "\tAttempting to use vector of pointers to access specialVehicles member functions: " << endl;
	if(vectorOfVehicles[0]->testFunctionCall()) {
		cout << "\tMember function called succsesfullly" << endl;
	}
	else {
		cout << "\tFailed to call member function" << endl;
	}


	int sizeOfVtwo = 3;
	bool vTwoIsVertical = true;
	int xCoord1VTwo = 3;
	int yCoord1VTwo = 4;
	int xCoord2VTwo = 3;
	int yCoord2VTwo = 5;
	int xCoord3VTwo = 3;
	int yCoord3VTwo = 6;

	int sizeOfVThree = 2;
	bool vThreeIsVertical = false;
	int xCoord1VThree = 3;
	int yCoord1VThree = 2;
	int xCoord2VThree = 4;
	int yCoord3VThree = 2;
	
	
	



}

//This is where we take the info from the file that GameSetup opens and turns it into vehicles on the board

