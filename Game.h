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
#include "Button.h"
#include "graphics.h"

using namespace std;


class Game {
private:
	Board board;
	ScoreMetrics metrics;	//keeps track of the score
	GameSetup theSetup;
	int randomSetupLowerBound;
	int randomSetupUpperBound;
	int currentSetup;	//store which number setup, so current one can be restarted & saved
	vector<unique_ptr<Vehicle>> vectorOfVehicles;	//Objects that move on the board
	int selectedVehicleIndex;	//An integer index in vectorOfVehicles. So that movement only applies to 1 vehicle at a time

	string progressFilename;

	bool debugPrintProgressFile;	//used for testing
	bool debugPrintPopulateBoard;

	vector<vector<double>> colors;	//vector of colors for the vehicles. Always drawn in the same order, 1st color is SpecialVehicle

	GlobalWindowPositions globalPositions;	//used to get shared constants
	string movesMessage;
	string statusMessage;
	
	Button saveButton = Button(saveButtonWidth, buttonHeight, buttonX, buttonY, "Save", Color{.1, .9, .1});
	Button loadButton = Button(loadButtonWidth, buttonHeight, loadButtonX, buttonY, "Load", Color{ 230/255.0, 152/255.0, 0});
	Button restartButton = Button(restartButtonWidth, buttonHeight, restartButtonX, buttonY, "Restart", Color{.9, .1, .1});
	Button newGameButton = Button(newGameButtonWidth, buttonHeight, newGameButtonX, buttonY, "New Game", Color{.1, .9, .1});

public:
	Game();		//default constructor has debug mode off
	Game(bool debugModeOn);		//setting option to print to screen on or off
	~Game();

	//Sets the board to the initial setup & redraws the vehicles
	void createGame();

	// Requires: nothing
	// Modifies: boolean debug variables
	// Effects: toggles debug variables to print or hide information about the game
	void setDebugPrintProgressFile(bool value);

	bool getDebugPrintProgressFile() const;

	void setDebugPrintPopulateBoard(bool value);

	bool getDebugPrintPopulateBoard() const;

	// Requires: nothing
	// Modifies: vectorOfvehicles
	// Effects: loops through all vehicles & makes them display the board after each movement
	void setDebugPrintVehicleLocations(bool printBoard);


	// Requires: INDEX in the range of the vector (>0 and < number of vehicles)
	// Modifies: selectedVehicleIndex
	// Effects: sets selectedVehicleIndex. Used when cursor() moves over a piece
	void setSelectedVehicleIndex(int vehicleIndex);

	int getSelectedVehicleIndex() const;

	//return pointer to currently selected vehicle. Movement only acts on this 1 vehicle at a time
	unique_ptr<Vehicle> const& getSelectedVehicle() const;

	// Return reference to vector of vehicles
	vector<unique_ptr<Vehicle>> const& getVehicles() const;

	ScoreMetrics& getMetrics();

	string getStatusMessage() const;

	void setStatusMessage(string message);

	//Methods to return reference to buttons to be called in graphics_started
	Button& getSaveButton();

	Button& getLoadButton();

	Button& getRestartButton();

	Button& getNewGameButton();

	// Requires: vector of integers with valid list of vehicles & coordinates
	// Modifies: board
	// Effects: parses a list of numbers & creates vehicles from their coordinates
	void populateBoard(vector<int> fileContents);

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

	//Pick a new random setup (different from the current one) & start the game
	void newGame();

	void restart();

	//Draws the board & buttons by calling various helper methods
	void draw() const;

	void drawButtons() const;

	void drawInstructions() const;

	//Draw the score (How many moves they made)
	void drawMoves() const;

	void setVehicleColors();
};

#endif