#ifndef Board_h
#define Board_h

#include <iostream>
#include <string>
#include <vector>
#include "Coordinate2D.h"
#include "GlobalWindowPositions.h"
#include "graphics.h"

using namespace std;

class Board {
private:
	vector<vector<bool>> occupiedSquares;
	Coordinate2D winningSpace;		//Used by Special Vehicle to check if it won the game

	GlobalWindowPositions globalPositions;	//used to get constants shared with Vehicle about positions & sizes
	int upperCornerX;
	int upperCornerY;
	int boardUpperCornerX;	//used by board so border extends on upper left of 1st square drawn
	int boardUpperCornerY;	//used by board so border extends on upper left of 1st square drawn
	int borderSize;		//
	int squareSize;		//how wide a square on the board is. Width of vehicle, used to draw board
	int squareSizeMinusBorder;		//how wide a square on the board is. Width of vehicle, used to draw board
	int boardPixelSpan; 	//make containing background square that's as big as the squares inside, but also accounts for the border
	int exitSquareUpperLeftX;
	int exitSquareUpperLeftY;

	string exitMessage;
	int exitSquareWidth;

	Color borderColor;
	Color squareColor;

public:
	Board();
	~Board();

	vector<vector<bool>> getOccupiedSquares() const;

	Coordinate2D getWinningSpace() const;

	// Requires: Nothing
	// Modifies: nothing
	// Effects: tells you if a given coordinate is the winning space
	bool isWinningSpace(int x, int y) const;

	// Requires: coordinate with x & y components inside valid board dimensions
	// Modifies: nothing
	// Effects: tells you if space is free. Takes in a Coordinate2D so that we don't confuse x & y of the coordiante with x & y of the vector (which are (y, x))
	bool isUnoccupiedSpace(int x, int y) const;

	// Requires: square to be a valid x, y coordinate in the vector & NOT a boundary, & not in a spot of any other Vehicle
	// Modifies: board
	// Effects: Sets a square in the board to FALSE (unoccupied when a vehicle moves away)
	void setSquareVacant(int x, int y);

	// Requires: square to be a valid x, y coordinate in the vector & NOT a boundary, & not in a spot of any other Vehicle
	// Modifies: board
	// Effects: Sets a square in the board to true (occupied)
	void setSquareOccupied(int x, int y);

	//Makes a grid of squares with borders
	void draw() const;

	void drawExitSquare() const;

	friend ostream& operator << (ostream& outStream, const Board& board);

private:
	// Requires: x & y as valid board coordiantes (not outside of range of vector)
	// Modifies: nothing / board
	// Effects: converts between x & y of a vehicle to x & y used by the board. (Vehicle is 6X6 and vector is 8X8 so add 1 to each parameter when accessing/changing)
	bool getSquareValueFromVehicleCoordinates(int x, int y) const;
	void setSquareValueFromVehicleCoordinates(int x, int y, bool value);
};

#endif
