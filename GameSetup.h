#ifndef GameSetup_hpp
#define GameSetup_hpp
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <random>
#include "Vehicle.h"
#include "HorizontalVehicle.h"
#include "VerticalVehicle.h"
#include "SpecialVehicle.h"

using namespace std;

class GameSetup {
private:
	vector<int> vehicleLocations;
	string setupFilename0;		//the specific setup the constructor should open
	string setupBaseFilename = "setup0";
	string setupExtension = ".txt";
	string defaultSetupFilename = "setup01.txt";

public:
	GameSetup();
	GameSetup(int setupNumber);
	~GameSetup();

	// Requires: lowerBound < higherBound
	// Modifies: nothing
	// Effects: returns a random number in the specified range
	static int getRandomInt(int lowerBound, int upperBound);

	vector<int> getSetupAsList() const;

	//static since any Game needs to be able to read files
	// Requires: a valid filename (does nothing if can't open), file must contain only integers
	// Modifies: nothing
	// Effects: reads a file of integers & returns a vector
	static vector<int> readFile(string filename);

	static void printVector(vector<int> vector);
};

#endif