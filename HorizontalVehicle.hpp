#ifndef HorizontalVehicle_hpp
#define HorizontalVehicle_hpp

#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.hpp"

using namespace std;

class HorizontalVehicle: public Vehicle {
private:
	//fields

public:
	HorizontalVehicle();
	HorizontalVehicle(vector<Coordinate2D> coordinates);
	~HorizontalVehicle();

	virtual bool moveUp() override;

	virtual bool moveDown() override;

	virtual bool moveLeft() override;

	virtual bool moveRight() override;
};

#endif