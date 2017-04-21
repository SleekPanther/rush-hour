#ifndef GameSetup_hpp
#define GameSetup_hpp
#include <memory>
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
	string setupFilename;		//the specific setup the constructor should open

	//For now I will out in a harcoded set of vehicles that will be loaded as the board set up. 
	//In the future this set up will come from a file. 

	//Create vector that will contain pointers to objects that instances of children of Vehicle class
	// vector<unique_ptr<Vehicle> > allVehicles;
	vector<Vehicle*> allVehicles;

public:
//The folowing four fields provide all the needed infro for a board set up. (special vehicle always first)
int numOfVehicles;
vector<int> vehicleLengths;
vector<Coordinate2D> allCoords;
		
	GameSetup();

	//This constructor WILL allow us to select from the set ups located in our save file
	GameSetup(int whichSetUp, Board theBoard);
	~GameSetup();

	// Requires: lowerBound < higherBound
	// Modifies: nothing
	// Effects: returns a random number in the specified range
	static int getRandomInt(int lowerBound, int upperBound);

	vector<int> getSetupAsList() const;

	//This method will return true untill all coordinates have been recieved and the vector of coordinates is empty
	bool thereAreMore();

	//static since any Game needs to be able to read files
	// Requires: a valid filename (does nothing if can't open), file must contain only integers
	// Modifies: nothing
	// Effects: reads a file of integers & returns a vector
	static vector<int> readFile(string filename);

	static void printVector(vector<int> vector);

	/*dataConversion
	Requires:A file in the same folder to get game setups from
	Modifies:The fields numOfVehicles, the vector vehicleLengths, the vector allCoords
	Effects:Method *WILL* open file, use the data to set the correct values in the above members. (The game class will then use this data to create vehicles on the board)
	*/
	void dataConversion();


};

#endif