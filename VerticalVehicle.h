#ifndef VerticalVehicle_h
#define VerticalVehicle_h

#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.h"

using namespace std;

class VerticalVehicle: public Vehicle {
private:
	//fields

public:
	VerticalVehicle();
	VerticalVehicle(Board & board, vector<Coordinate2D> coordinates);
	~VerticalVehicle();

	virtual bool moveUp() override;

	virtual bool moveDown() override;

	virtual bool moveLeft() override;

	virtual bool moveRight() override;
};

#endif