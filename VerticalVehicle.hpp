#ifndef VerticalVehicle_hpp
#define VerticalVehicle_hpp

#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.hpp"

using namespace std;

class VerticalVehicle: public Vehicle {
private:
	//fields

public:
	VerticalVehicle();
	~VerticalVehicle();

	virtual bool moveUp() override;

	virtual bool moveDown() override;

	virtual bool moveLeft() override;

	virtual bool moveRight() override;
};

#endif