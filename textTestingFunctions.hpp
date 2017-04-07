#ifndef textTestingFunctions_hpp
#define textTestingFunctions_hpp

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>
#include "Vehicle.hpp"
#include "HorizontalVehicle.hpp"
#include "VerticalVehicle.hpp"
#include "SpecialVehicle.hpp"
#include "ScoreMetrics.hpp"
#include "Coordinate2D.hpp"
#include "Board.hpp"
#include "GameSetup.hpp"
#include "Game.hpp"


using namespace std;

//Runs all tests
void runAllTests();


bool test_Game();

bool test_GameSetup();

bool test_Board();

bool test_Coordinate2D();

bool test_Vehicle();

bool test_ScoreMetrics();

#endif