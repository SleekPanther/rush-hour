#ifndef SpecialVehicle_hpp
#define SpecialVehicle_hpp

#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.hpp"
#include "HorizontalVehicle.hpp"

using namespace std;

class SpecialVehicle : public HorizontalVehicle {
private:
	//fields

public:
	SpecialVehicle();
	~SpecialVehicle();

};

#endif