#ifndef Board_h
#define Board_h

#include <iostream>
#include <string>
#include <vector>
#include "Coordinate2D.h"

using namespace std;

class Board {
private:
	vector<vector<bool>> occupiedSquares;
	Coordinate2D winningSpace;		//Used by Special Vehicle to check if it won the game

public:
	Board();
	~Board();

	vector<vector<bool>> getOccupiedSquares() const;

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

	Coordinate2D getWinningSpace() const;

	// Requires: Nothing
	// Modifies: nothing
	// Effects: tells you if a given coordinate is the winning space
	bool isWinningSpace(int x, int y) const;

	void draw();

	friend ostream& operator << (ostream& outStream, const Board& board);

private:
	// Requires: x & y as valid board coordiantes (not outside of range of vector)
	// Modifies: nothing / board
	// Effects: converts between x & y of a vehicle to x & y used by the board. (Vehicle is 6X6 and vector is 8X8 so add 1 to each parameter when accessing/changing)
	bool getSquareValueFromVehicleCoordinates(int x, int y) const;
	void setSquareValueFromVehicleCoordinates(int x, int y, bool value);
};

#endif
