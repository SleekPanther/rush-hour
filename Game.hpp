#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Vehicle.hpp"
#include "HorizontalVehicle.hpp"
#include "VerticalVehicle.hpp"
#include "SpecialVehicle.hpp"
#include "ScoreMetrics.hpp"
#include "Coordinate2D.hpp"
#include "Board.hpp"
#include "GameSetup.hpp"


using namespace std;

class Game{
private:
	//fields

public:
	Game();
	~Game();

	vector<Vehicle> getVehicles();
};

#endif