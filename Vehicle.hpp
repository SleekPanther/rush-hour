#ifndef Vehicle_hpp
#define Vehicle_hpp

#include <iostream>
#include <string>
#include <vector>
#include "Coordinate2D.hpp"
#include "Board.hpp"

using namespace std;

class Vehicle {
protected:
	vector<Coordinate2D> coordinates;
	Board board;
	// Color color;

public:
	Vehicle();		//shouldn't keep default constructor for long
	Vehicle(Board board, vector<Coordinate2D> coordinates);
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
};

#endif