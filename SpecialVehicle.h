#ifndef SpecialVehicle_h
#define SpecialVehicle_h

#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.h"
#include "HorizontalVehicle.h"

using namespace std;

//only SpecialVehicle can ever be in the position to leave the board. Therefore moving right into the only unoccupied boundary square wins the game

class SpecialVehicle : public HorizontalVehicle {
public:
	SpecialVehicle(Board & board, vector<Coordinate2D> coordinates);
	~SpecialVehicle();

	virtual string getVehicleType() const override;

	// Requires: nothing
	// Modifies: inWinningSpace & board
	// Effects: checks if any of the new coordinates are the winning space
	virtual bool moveRight() override;
};

#endif