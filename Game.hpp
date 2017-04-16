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

//Needs to call isInWinningSpace() after each Vehicle moves to see if the game should be over

class Game{
private:
	Board board;

public:
	Game();
	~Game();

	vector<Vehicle> getVehicles();
};

#endif