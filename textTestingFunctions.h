#ifndef textTestingFunctions_hpp
#define textTestingFunctions_hpp

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>
#include "Vehicle.h"
#include "HorizontalVehicle.h"
#include "VerticalVehicle.h"
#include "SpecialVehicle.h"
#include "ScoreMetrics.h"
#include "Coordinate2D.h"
#include "Board.h"
#include "GameSetup.h"
#include "Game.h"


using namespace std;

void runAllTests();


bool test_Game();

bool test_GameSetup();

bool test_Board();

bool test_Coordinate2D();

bool test_Vehicle();

bool test_ScoreMetrics();



#endif