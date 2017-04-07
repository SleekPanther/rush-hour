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
private:
	//fields

public:
	Vehicle();
	~Vehicle();

	virtual bool moveUp() = 0;

	virtual bool moveDown() = 0;

	virtual bool moveLeft() = 0;

	virtual bool moveRight() = 0;
};

#endif