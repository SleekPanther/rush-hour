#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "GameSetup.hpp"
#include "Board.hpp"
#include "ScoreMetrics.hpp"
#include "HorizontalVehicle.hpp"
#include "VerticalVehicle.hpp"
#include "SpecialVehicle.hpp"

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