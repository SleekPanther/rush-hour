#ifndef Vehicle_h
#define Vehicle_h

#include <iostream>
#include <string>
#include <vector>
#include "Coordinate2D.h"
#include "Board.h"
#include "graphics.h"

using namespace std;

enum class VehicleGlowState {lightening, darkening};

class Vehicle {
protected:
	vector<Coordinate2D> coordinates;
	Board & board;		//so the piece knows where to be drawn.		MUST BE A REFERENCE
	Color color;
	Color initialColor;	//used to go back to it's orignal color when not hovered
	VehicleGlowState colorGlowState;

	bool inWinningSpace;

	bool debugPrintBoard;		//set true to display the contents of the board after each move method, false when not debugging

public:
	Vehicle(Board & board, vector<Coordinate2D> coordinates);
	~Vehicle();

	// Requires: nothing
	// Modifies: debugPrintBoard
	// Effects: toggles debug information to print board after every move
	void setDebugPrintBoard(bool debugPrintBoardOn);

	bool getDebugPrintBoard() const;

	vector<Coordinate2D> getCoordinates() const;

	// Requires: nothing
	// Modifies: nothing
	// Effects: calculates & returns length of vehicle based on number of coordinates
	int getLength() const;

	// Requires: 3 doubles between 0 & 1
	// Modifies: color field
	// Effects: sets the color from an input vector
	void setColor(vector<double> rbg);

	void Vehicle::setColor(Color newColor);

	Color getColor() const;

	void setInitialColor(vector<double> rbg);

	Color getInitialColor() const;

	bool isColorMaxed() const;

	bool isColorInitial() const;

	bool shouldLighten() const;

	bool shouldDarken() const;

	void setLighten();

	void setDarken();
	
	// Requires: nothing
	// Modifies: nothing
	// Effects: prints coordinates on screen for testing
	void printCoordinates() const;

	// Requires: nothing
	// Modifies: nothing
	// Effects: gets a string of the vehicle's coordinates
	string getStringCoordinates() const;

	// Requires: nothing
	// Modifies: nothing
	// Effects: called in move() methods to print lovations (only if debug mode is ont)
	void printBoardAndCoordinatesIfDebug() const;

	// Requires: nothing
	// Modifies: nothing
	// Effects: returns "vertical" or "horizontal" to differentate between vehicle.
	virtual string getVehicleType() const = 0;

	virtual bool moveUp() = 0;

	virtual bool moveDown() = 0;

	virtual bool moveLeft() = 0;

	virtual bool moveRight() = 0;

	// Requires: nothing
	// Modifies: board
	// Effects: sets all coordinates of the vehicle to false in the board, so moving can be calculated without the vehicle itself getting in the way
	void vacateBoard();

	// Requires: nothing
	// Modifies: board
	// Effects: loops over coordinates and re-adds the vehicle to board (used after the move methods check if the vehicle can move)
	void reOccupyBoard();

	// Requires: nothing
	// Modifies: nothing
	// Effects: tells you if the vehicle is the square that wins the game. Only applies for SpecialVehicle
	bool isInWinningSpace() const;

	void draw() const;

	// Requires: nothing
	// Modifies: nothing
	// Effects: checks if a (x, y) point is inside the vehicle boundary
	bool isOverlapping(int mouseX, int mouseY) const;
};

#endif