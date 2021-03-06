#ifndef HorizontalVehicle_h
#define HorizontalVehicle_h

#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.h"

using namespace std;

class HorizontalVehicle: public Vehicle {
public:
	HorizontalVehicle(Board & board, vector<Coordinate2D> coordinates);
	~HorizontalVehicle();

	virtual string getVehicleType() const override;

	virtual bool moveUp() override;

	virtual bool moveDown() override;

	virtual bool moveLeft() override;

	virtual bool moveRight() override;
};

#endif