#ifndef textTestingFunctions_h
#define textTestingFunctions_h

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <iostream>
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


void chooseLoadSave();

#endif