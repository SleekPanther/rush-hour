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

//IMPORTANT game must call isInWinningSpace() after EVERY attempted move, otherwise SpecialVehicle will check vector indexes that don't exist

class Game {
private:
	Board board;
	GameSetup theSetup;
	vector<unique_ptr<Vehicle>> vectorOfVehicles;
	ScoreMetrics metrics;

	string progressFilename;
	string defaultSetupFilename;

	bool debugPrintProgressFile;
	bool debugPrintPopulateBoard;

public:
	Game();
	Game(bool debugModeOn);		//calls other constructor setting debug mode on or off
	~Game();

	// Requires: nothing
	// Modifies: boolean debug variables
	// Effects: toggles debug variables to print or hide information about the game
	void setDebugPrintProgressFile(bool value);

	bool getDebugPrintProgressFile() const;

	void setDebugPrintPopulateBoard(bool value);

	bool getDebugPrintPopulateBoard() const;

	// Requires: vector of integers with valid list of vehicles & coordinates
	// Modifies: board
	// Effects: parses a list of numbers & creates vehicles from their coordinates
	void populateBoard(vector<int> fileContents);

	// Requires: nothing
	// Modifies: board
	// Effects: calls overloaded load() to load the default progress file
	void load();

	// Requires: progress file to have valid contents, or not exist (throws errors when reading from non-valid setups)
	// Modifies: board & vectorOfVehicles
	// Effects: loads a specific file to resume playback
	void load(string filename);

	// Requires: nothing
	// Modifies: progress file
	// Effects: loops over vectorOfVehicles & converts current positions to text information about the game state
	void save();
};

#endif