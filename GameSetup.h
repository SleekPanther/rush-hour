#ifndef GameSetup_hpp
#define GameSetup_hpp
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.h"
#include "HorizontalVehicle.h"
#include "VerticalVehicle.h"
#include "SpecialVehicle.h"

using namespace std;

class GameSetup {
private:
	//fields
	//For now I will out in a harcoded set of vehicles that will be loaded as the board set up. 
	//In the future this set up will come from a file. 

	//Create vector that will contain pointers to objects that instances of children of Vehicle class
	vector<unique_ptr<Vehicle> > allVehicles;
	//vector<Vehicle*> allVehicles;

public:
	    //The folowing four fields provide all the needed infro for a board set up. (special vehicle always first)
		int numOfVehicles;
		vector<int> vehicleLengths;
		vector<Coordinate2D> allCoords;
		
	GameSetup();
	//This constructor WILL allow us to select from the set ups located in our save file
	GameSetup(int whichSetUp, Board theBoard);
	~GameSetup();
	//This method will return true untill all coordinates have been recieved and the vector of coordinates is empty
	bool thereAreMore();
	/*dataConversion
	Requires:A file in the same folder to get game setups from
	Modifies:The fields numOfVehicles, the vector vehicleLengths, the vector allCoords
	Effects:Method *WILL* open file, use the data to set the correct values in the above members. (The game class will then use this data to create vehicles on the board)
	*/
	void dataConversion();


};

#endif