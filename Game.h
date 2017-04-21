#ifndef Game_h
#define Game_h

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Vehicle.h"
#include "HorizontalVehicle.h"
#include "VerticalVehicle.h"
#include "SpecialVehicle.h"
#include "ScoreMetrics.h"
#include "Coordinate2D.h"
#include "Board.h"
#include "GameSetup.h"


using namespace std;

//Needs to call isInWinningSpace() after each Vehicle moves to see if the game should be over
//IMPORTANT game must call isInWinningSpace() after EVERY attempted move, otherwise SpecialVehicle will check vector indexes that don't exist

class Game {
private:
	Board board;
	GameSetup theSetup;
	ScoreMetrics metrics;

	vector<unique_ptr<Vehicle>> vectorOfVehicles;

	string progressFilename;
	string defaultSetupFilename;

	bool debugPrintProgressFile;

public:
	Game();
	~Game();

	// Requires: nothing
	// Modifies: setDebugPrintProgressFile
	// Effects: Sets the value of setDebugPrintProgressFile. Allows you to see the contents of what's being printed to the progress file in save()
	void setDebugPrintProgressFile(bool value);

	bool getDebugPrintProgressFile() const;

	//This is a vector of vehicle pointers that point to all the vehicles defined by the set up and then updated as the game progresses
	vector<Vehicle> getVehicles();

	void populateBoard(vector<int> fileContents);

	void load();

	void save();
	
	/*tretrieveVehicles uses the information accesed from gameSetup to create the correct vehicles
	*that will then be pointed to by the vector of vehicle pointers
	*Requiers: File to exist in same folder and for it to be of the correct format
	*Modifies: The vector of pointers to vehicles in this class
	*Effects: Creates the set of vehicles from a given set up and adds pointers to them to the vector of pointers
	*/
	void retrieveVehicles(Board theBoard);
};

#endif