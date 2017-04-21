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
	bool debugPrintPopulateBoard;

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

	bool getDebugPrintPopulateBoard() const;

	// Requires: nothing
	// Modifies: debugPrintPopulateBoard
	// Effects: used to toggle debug info on/off
	void setDebugPrintPopulateBoard(bool value);

	void populateBoard(vector<int> fileContents);

	// Requires: nothing
	// Modifies: board
	// Effects: calls overloaded load() to load the default progress file
	void load();

	// Requires: progress file to have valid contents, or not exist (throws errors when reading from non-valid setups)
	// Modifies: board & vectorOfVehicles
	// Effects: loads a specific file to resume playback
	void load(string filename);

	void save();
};

#endif