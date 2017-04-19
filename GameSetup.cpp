#include "GameSetup.h"
#include <fstream>
#include <iostream>


GameSetup::GameSetup() {
	cout << "\tnew game setup" << endl;
	dataConversion();
}

GameSetup::GameSetup(int whichSetUp, Board theBoard)
{

	
}

GameSetup::~GameSetup() {
}

bool GameSetup::thereAreMore()
{
	return true;
}

void GameSetup::dataConversion()
{
	ifstream inputFile;                        //Open the file
	inputFile.open("setUps.txt");
	cout << "\t  -Attempting to open file:" << endl;
	if (inputFile) {//If file opes succsesfully
		cout << "\t  -File successfully oppened in GameSetup Constructor" << endl;
		
		
		double next;//create double value that will hold numbers 
		for (int i = 0; i < 4; i++) {//Print each of the values formatted
			
			inputFile >> next;
			cout << "\t  -This should display the int that is in position " << i << " in the inputFile:  ";
			cout << next << endl;

		}//End of loop that reads in values from file

	}//End of if statement checking if file opened succsesfully
	
	inputFile.close();//Close the file
	//This is just test code, correct values will come from a file. 

	numOfVehicles = 2;

	vehicleLengths.push_back(2);
	vehicleLengths.push_back(2);

	Coordinate2D firstCoord(2, 3);
	Coordinate2D secondCoord(3, 3);
	allCoords.push_back(firstCoord);
	allCoords.push_back(secondCoord);

	Coordinate2D thirdCoord(4, 4);
	Coordinate2D fourthCoord(4, 3);
	allCoords.push_back(thirdCoord);
	allCoords.push_back(fourthCoord);





	//Now we push back a pointer to a new vehicle that we create using the values above. 
	//allVehicles.push_back(make_unique<HorizontalVehicle>(theBoard, theCoords));
}
