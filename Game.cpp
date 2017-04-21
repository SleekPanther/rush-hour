#include "Game.h"

Game::Game() {
	debugPrintPopulateBoard=true;
	progressFilename = "progress.txt";
	//Empty Board is already set up

	vectorOfVehicles.push_back(make_unique<SpecialVehicle>(board, vector<Coordinate2D>{ Coordinate2D(4, 2), Coordinate2D(3, 2)}));
	vectorOfVehicles.push_back(make_unique<HorizontalVehicle>(board, vector<Coordinate2D>{ Coordinate2D(2, 4), Coordinate2D(3, 4)}));
	vectorOfVehicles.push_back(make_unique<VerticalVehicle>(board, vector<Coordinate2D>{ Coordinate2D(1, 0), Coordinate2D(1, 1)}));

	//retrieveVehicles(board);
}

Game::~Game() {
}

vector<Vehicle> Game::getVehicles() {
	return vector<Vehicle>();
}

bool Game::getGebugPrintPopulateBoard() const{
	return debugPrintPopulateBoard;
}

void Game::setDebugPrintPopulateBoard(bool value){
	debugPrintPopulateBoard=value;
}

void Game::load() {
	ifstream inputFile(progressFilename);
	if (inputFile) {		//if the file exists, attempt to load progress
		vector<int> fileContents = GameSetup::readFile(progressFilename);
		// GameSetup::printVector(fileContents);
		int previousScore;
		inputFile >> previousScore;		//save 1st number in file
		fileContents.erase(fileContents.begin());	//erase the 1st number to just get the vehicles & coordinates
													// GameSetup::printVector(fileContents);
		metrics.setMoveCount(previousScore);
		populateBoard(fileContents);
		
	}
	else {
		//start new setup
	}
}

void Game::save() {
	string allVehicleInfo = "";		//string appended to while parsing the board, written to the file at the end
	string horizontalInfo = "";
	string verticalInfo = "";
	int horizontalCount = 0;
	int verticalCount = 0;

	//deal with special vehicle 1st
	int vehicleLength = vectorOfVehicles[0]->getLength();
	allVehicleInfo = allVehicleInfo + to_string(vehicleLength) + "\n";
	vector<Coordinate2D> coords = vectorOfVehicles[0]->getCoordinates();
	for (int i = 0; i<vehicleLength; i++) {			//add each (x, y) coordinate separated by spaces
		allVehicleInfo = allVehicleInfo + to_string(coords[i].x) + " ";
		allVehicleInfo = allVehicleInfo + to_string(coords[i].y) + " ";
	}
	allVehicleInfo += "\n";

	//start loop from 1 since alread added special vehicle
	for (int i = 1; i<vectorOfVehicles.size(); i++) {
		string type = vectorOfVehicles[i]->getVehicleType();		//to differentate between abstract vehicles
		if (type == "horizontal") {
			horizontalCount++;		//we found a horizontal vehicle
			vehicleLength = vectorOfVehicles[i]->getLength();
			horizontalInfo = horizontalInfo + to_string(vehicleLength) + "\n";
			coords = vectorOfVehicles[i]->getCoordinates();
			for (int j = 0; j<vehicleLength; j++) {			//add each (x, y) coordinate separated by spaces
				horizontalInfo = horizontalInfo + to_string(coords[j].x) + " ";
				horizontalInfo = horizontalInfo + to_string(coords[j].y) + " ";
			}
			horizontalInfo += "\n";
		}
		else if (type == "vertical") {
			verticalCount++;		//we found a vertical vehicle
			vehicleLength = vectorOfVehicles[i]->getLength();
			verticalInfo = verticalInfo + to_string(vehicleLength) + "\n";
			coords = vectorOfVehicles[i]->getCoordinates();
			for (int j = 0; j<vehicleLength; j++) {			//add each (x, y) coordinate separated by spaces
				verticalInfo = verticalInfo + to_string(coords[j].x) + " ";
				verticalInfo = verticalInfo + to_string(coords[j].y) + " ";
			}
			verticalInfo += "\n";
		}
	}

	//insert horizontal and vertical counts at the ver beginning of the string
	allVehicleInfo.insert(0, to_string(horizontalCount));
	allVehicleInfo.insert(1, " ");		//add a space between 2 numbers
	allVehicleInfo.insert(2, to_string(horizontalCount));
	allVehicleInfo.insert(3, "\n");		//add newline

										//append horizontal & vertical coordinates to string
	allVehicleInfo = allVehicleInfo + horizontalInfo + verticalInfo;

	//save to file
	cout << allVehicleInfo << endl;

}

void Game::populateBoard(vector<int> fileContents) {
	vectorOfVehicles.clear();
	int numOfVertical = fileContents[0];
	int numOfHorizontal = fileContents[1];
	int lengthOfSpecial = fileContents[2];
	
	//Temp vector that will be used for all vehicles
	vector<Coordinate2D> tempCoordinates;
	
	//CREATE SPECIAL PIECE 
	//Use loop to create vector of coordinates
	for (int i = 0; i < lengthOfSpecial; i++) {
		Coordinate2D temp(fileContents[3+i], fileContents[4+i]);
		
		tempCoordinates.push_back(temp);
	}
	vectorOfVehicles.push_back(make_unique<SpecialVehicle>(board, tempCoordinates));
	tempCoordinates.clear();

	
	
	//Ofset starts at 8 as that is how many values 
	int offset = 2;
	//CREATE VERTICAL VEHICLES
	for (int i = 0; i < numOfVertical; i++) {
		//This offset allows loop to take correct values regardless of the number of vertical cars
		//Take in as many coordinate as needed
		int lengthOfThisVertical = fileContents[6 +offset];
			for(int j = 0; j < lengthOfThisVertical; j++) {
				Coordinate2D temp(fileContents[8 + 2 * j], fileContents[9 + 2 * j]);
				tempCoordinates.push_back(temp);		
			}//End of loop that collects all the coordinates for a single vertical vehicle
			//for (int i = 0; i < tempCoordinates.size(); i++) {cout << tempCoordinates[i];}
		
			//Create the vertical vehicle from this loop and add the pointer to the vector of pointers
			vectorOfVehicles.push_back(make_unique<VerticalVehicle>(board, tempCoordinates));
			offset += (1 + 2 * lengthOfThisVertical);
			
	}//End of create all vertical vehicles loop
	
	tempCoordinates.clear();
	
	offset += 5;
	int startIndexOfHorizontal = offset;
	int newOffset = 0;
	//HORIZONTAL VEHICLES
	for (int i = 0; i < numOfHorizontal; i++) {
		//Take in as many coordinate as needed
		int lengthOfThisHorizontal = fileContents[startIndexOfHorizontal + newOffset];
		for (int j = 0; j < lengthOfThisHorizontal; j++) {
			Coordinate2D temp(fileContents[startIndexOfHorizontal + 1 + 2 * j + newOffset], fileContents[startIndexOfHorizontal + 2 + 2 * j + newOffset]);
			tempCoordinates.push_back(temp);
		}//End of loop that collects all the coordinates for a single vertical vehicle
		 //Create the vertical vehicle from this loop and add the pointer to the vector of pointers
		vectorOfVehicles.push_back(make_unique<HorizontalVehicle>(board, tempCoordinates));
		newOffset += (1 + 2 * lengthOfThisHorizontal);
		tempCoordinates.clear();
		
	}//End of create all horizontal vehicles loop

	if(debugPrintPopulateBoard){
		cout << "populateBoard()\n";
		for (int i=0; i < vectorOfVehicles.size(); i++) {
			cout << "Vehicle number " << i << " is a "<< vectorOfVehicles[i]->getVehicleType()<< " Vehicle. And it has these coordinates: "<<endl; 
			vectorOfVehicles[i]->printCoordinates();
		}
	}
}

void Game::retrieveVehicles(Board theBoard)
{//Hard coded values used for testing, these values will be retrived from the set up file via a gameSetup member function
 // int numOfVehicles = 3;

 // //Each of the groups of six/eight values below represent all of the info required to set up vehicles.  
 // int sizeOfVOne = 2;
 // bool vOneIsVertical = false;
 // int xCoord1VOne = 1;
 // int yCoord1VOne = 3;
 // int xCoord2VOne = 2;
 // int yCoord2VOne = 3;
 // Coordinate2D v1FirstCoord(xCoord1VOne, yCoord1VOne);
 // Coordinate2D v1SecondCoord(xCoord2VOne, yCoord2VOne);
 // vector<Coordinate2D> vectOfCoords;
 // vectOfCoords.push_back(v1FirstCoord);
 // vectOfCoords.push_back(v1SecondCoord);
 // //Now create this special vehicle passing first a board and second a vector of coordinates
 // SpecialVehicle special(theBoard, vectOfCoords);
 // //Create a pointer to this vehicle
 // Vehicle * specialPoint = &special;
 // //Add this pointer to the array of pointers
 // vectorOfVehicles.push_back(specialPoint);
 // //Test to see if we are able to call member functions on this vehicle via the vector of pointers
 // cout << "\tAttempting to use vector of pointers to access specialVehicles member functions: " << endl;
 // if(vectorOfVehicles[0]->testFunctionCall()) {
 // 	cout << "\tMember function called succsesfullly" << endl;
 // }
 // else {
 // 	cout << "\tFailed to call member function" << endl;
 // }


 // int sizeOfVtwo = 3;
 // bool vTwoIsVertical = true;
 // int xCoord1VTwo = 3;
 // int yCoord1VTwo = 4;
 // int xCoord2VTwo = 3;
 // int yCoord2VTwo = 5;
 // int xCoord3VTwo = 3;
 // int yCoord3VTwo = 6;

 // int sizeOfVThree = 2;
 // bool vThreeIsVertical = false;
 // int xCoord1VThree = 3;
 // int yCoord1VThree = 2;
 // int xCoord2VThree = 4;
 // int yCoord3VThree = 2;






}

//This is where we take the info from the file that GameSetup opens and turns it into vehicles on the board

