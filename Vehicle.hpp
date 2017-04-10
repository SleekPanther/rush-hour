#ifndef Vehicle_hpp
#define Vehicle_hpp

#include <iostream>
#include <string>
#include <vector>
#include "Coordinate2D.hpp"
#include "Board.hpp"

//CANNOT INCLUDE GAME, for some reason it breaks it.
//maybe vehicle is being included twice somehow
// #include "Game.hpp"

using namespace std;

class Vehicle {
protected:
	vector<Coordinate2D> coordinates;
	// Color color;

public:
	Vehicle();		//shouldn't keep default constructor for long
	Vehicle(vector<Coordinate2D> coordinates);
	~Vehicle();

	vector<Coordinate2D> getCoordinates() const;

	virtual bool moveUp() = 0;

	virtual bool moveDown() = 0;

	virtual bool moveLeft() = 0;

	virtual bool moveRight() = 0;
};

#endif