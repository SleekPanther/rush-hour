#include "Game.h"

Game::Game() : Game(false) {
}

Game::Game(bool debugModeOn){
	progressFilename="progress.txt";
	debugPrintProgressFile = debugModeOn;		//change this to NOT print progress to screen when saving
	debugPrintPopulateBoard = debugModeOn;

	//Empty Board is already set up
	//GameSetup constructor created a default layout, use it to populate the board
	populateBoard(theSetup.getSetupAsList());
	selectedVehicle=0;		//choose the 0th item in vectorOfVehicle (the SpecialVehicle)
}

Game::~Game() {
}

void Game::setDebugPrintProgressFile(bool value){
	debugPrintProgressFile=value;
}

bool Game::getDebugPrintProgressFile() const{
	return debugPrintProgressFile;
}

void Game::setDebugPrintPopulateBoard(bool value){
	debugPrintPopulateBoard=value;
}

bool Game::getDebugPrintPopulateBoard() const{
	return debugPrintPopulateBoard;
}


void Game::load(){
	load(progressFilename);
}

void Game::load(string filename) {
	ifstream inputFile(filename);
	if (inputFile) {		//if the file exists, attempt to load progress
		vector<int> fileContents = GameSetup::readFile(filename);
		int previousScore;
		inputFile >> previousScore;		//save 1st number in file
		fileContents.erase(fileContents.begin());	//erase the 1st number to just get the vehicles & coordinates

		metrics.setMoveCount(previousScore);
		populateBoard(fileContents);
	}
	else{
		cout << "There was no game saved" << endl;
	}
	inputFile.close();
}

void Game::save() {
	string allVehicleInfo = "";		//string appended to while parsing the board, written to the file at the end
	string horizontalInfo = "";
	string verticalInfo = "";
	int horizontalCount = 0;
	int verticalCount = 0;

	//Save current score of game
	int currentMoveCount = metrics.getMoveCount();
	allVehicleInfo = allVehicleInfo + to_string(currentMoveCount) + "\n\n";		//add 2 newlines after to differentiate from vehicle info

	//deal with special vehicle 1st
	int vehicleLength = vectorOfVehicles[0]->getLength();
	allVehicleInfo = allVehicleInfo + to_string(vehicleLength) + "\n";
	vector<Coordinate2D> coords = vectorOfVehicles[0]->getCoordinates();
	for (int i = 0; i<vehicleLength; i++) {			//add each (x, y) coordinate separated by spaces
		allVehicleInfo = allVehicleInfo + to_string(coords[i].x) + " ";
		allVehicleInfo = allVehicleInfo + to_string(coords[i].y) + " ";
	}
	allVehicleInfo += "\n";

	//start loop from 1 since already added special vehicle
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
	//first calculate the length of the score (how many digits) to see where to insert the other vehicle info
	int currentMoveCountLength = to_string(currentMoveCount).length();		//how many digits long the number is
	int newlineCount = 2;		//above we added 2 newlines after the score
	int vehicleInfStringOffset = currentMoveCountLength + newlineCount;		//how many characters in de we insert the data for horizontalCount & verticalCount

	//insert 2 vehicle counts with separation characters afterward, starting from vehicleInfStringOffset and increasing by 1 every time
	allVehicleInfo.insert(vehicleInfStringOffset, to_string(horizontalCount));		//1st 1-3 characters are number of moves, followed by 5 blank lines so insert after those
	allVehicleInfo.insert(vehicleInfStringOffset+1, " ");		//add a space between 2 numbers
	allVehicleInfo.insert(vehicleInfStringOffset+2, to_string(horizontalCount));
	allVehicleInfo.insert(vehicleInfStringOffset+3, "\n");		//add newline

	//append horizontal & vertical coordinates to string
	allVehicleInfo = allVehicleInfo + horizontalInfo + verticalInfo;

	if(debugPrintProgressFile){		//only display for testing
		cout << "Text to be written to Progress File:\n" << allVehicleInfo << endl;
	}

	//save to file
	ofstream progressFile(progressFilename);
	if(progressFile){
		progressFile << allVehicleInfo;
	}
	progressFile.close();
}

void Game::populateBoard(vector<int> fileContents) {
	board = Board();	//clear the board
	vectorOfVehicles.clear();

	int vectorIteratorIndex = 0;		//go through all vector indexes, incrementing as each number has been read

	int numOfHorizontal = fileContents[vectorIteratorIndex++];
	int numOfVertical = fileContents[vectorIteratorIndex++];
	int lengthOfSpecial = fileContents[vectorIteratorIndex++];
	
	vector<Coordinate2D> tempCoordinates;	//Temp vector that will be used for all vehicles
	int xComponentIndex, yComponentIndex;	//updated for every coordinate created


	//CREATE SPECIAL VEHICLE 
	//loop over length of vehicle to create vector of coordinates
	for (int i = 0; i < lengthOfSpecial; i++) {
		xComponentIndex = vectorIteratorIndex++;
		yComponentIndex = vectorIteratorIndex++;
		tempCoordinates.push_back( Coordinate2D(fileContents[xComponentIndex], fileContents[yComponentIndex]) );
	}
	vectorOfVehicles.push_back(make_unique<SpecialVehicle>(board, tempCoordinates));
	tempCoordinates.clear();


	//HORIZONTAL VEHICLES
	for (int i = 0; i < numOfHorizontal; i++) {
		//Take in as many coordinate as needed
		int lengthOfThisHorizontal = fileContents[vectorIteratorIndex++];
		for (int j = 0; j < lengthOfThisHorizontal; j++) {
			xComponentIndex = vectorIteratorIndex++;
			yComponentIndex = vectorIteratorIndex++;
			tempCoordinates.push_back( Coordinate2D(fileContents[xComponentIndex], fileContents[yComponentIndex]) );
		}//End of loop that collects all the coordinates for a single vertical vehicle

		 //Create the vertical vehicle from this loop and add the pointer to the vector of pointers
		vectorOfVehicles.push_back(make_unique<HorizontalVehicle>(board, tempCoordinates));

		tempCoordinates.clear();
	}//End of create all horizontal vehicles loop
	
	
	//CREATE VERTICAL VEHICLES
	for (int i = 0; i < numOfVertical; i++) {
		//Take in as many coordinate as needed
		int lengthOfThisVertical = fileContents[vectorIteratorIndex++];
		for(int j = 0; j < lengthOfThisVertical; j++) {
			xComponentIndex = vectorIteratorIndex++;
			yComponentIndex = vectorIteratorIndex++;
			tempCoordinates.push_back( Coordinate2D(fileContents[xComponentIndex], fileContents[yComponentIndex]) );
		}//End of loop that collects all the coordinates for a single vertical vehicle

		//Create the vertical vehicle from this loop and add the pointer to the vector of pointers
		vectorOfVehicles.push_back(make_unique<VerticalVehicle>(board, tempCoordinates));

		tempCoordinates.clear();
	}//End of create all vertical vehicles loop


	if(debugPrintPopulateBoard){
		cout << "populateBoard()\n";
		for (int i=0; i < vectorOfVehicles.size(); i++) {
			cout << "Vehicle [" << i << "] is a "<< vectorOfVehicles[i]->getVehicleType()<< " Vehicle. " << vectorOfVehicles[i]->getStringCoordinates() << '\n'; 
		}
		cout << "Board with vehicles from populateBoard()\n" << board << '\n';
	}
}