#ifndef SpecialVehicle_hpp
#define SpecialVehicle_hpp

#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.hpp"
#include "HorizontalVehicle.hpp"

using namespace std;

//only SpecialVehicle can ever be in the position to leave the board. Therefore moving right into the only unoccupied boundary square wins the game

class SpecialVehicle : public HorizontalVehicle {
private:
	//fields

public:
	SpecialVehicle();
	~SpecialVehicle();

};

#endif