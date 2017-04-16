#ifndef Vehicle_hpp
#define Vehicle_hpp

#include <iostream>
#include <string>
#include <vector>
#include "Coordinate2D.hpp"
#include "Board.hpp"

using namespace std;

//Draw should draw indivual rectangles & just joined together due to proximity
//Hovering over a piece should lighten the color
// or we could have a function constantly changing to color to make it glow

class Vehicle {
protected:
	vector<Coordinate2D> coordinates;
	Board & board;		//so the piece knows where to be drawn.		MUST BE A REFERENCE
	// Color color;
	bool inWinningSpace;

	bool debugPrintBoard;		//set true to display the contents of the board after each move method, false when not debugging

public:
	Vehicle(Board & board, vector<Coordinate2D> coordinates);
	~Vehicle();

	vector<Coordinate2D> getCoordinates() const;

	// Requires: nothing
	// Modifies: nothing
	// Effects: calculates & returns length of vehicle based on number of coordinates
	int getLength() const;

	// Requires: nothing
	// Modifies: nothing
	// Effects: prints coordinates on screen for testing
	void printCoordinates() const;

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

	void draw();
};

#endif