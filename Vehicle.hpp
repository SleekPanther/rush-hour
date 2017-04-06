#ifndef Vehicle_hpp
#define Vehicle_hpp

#include <iostream>
#include <string>
#include <vector>
#include "Game.hpp"
#include "Board.hpp"
#include "Coordinate2D.hpp"

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