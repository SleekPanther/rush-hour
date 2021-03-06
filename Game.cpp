#include "Game.h"

Game::Game() : Game(false) {
}

Game::Game(bool debugModeOn){
	progressFilename=".delete_this_file_if_program_dies";
	debugPrintProgressFile = debugModeOn;		//change this to NOT print progress to screen when saving
	debugPrintPopulateBoard = debugModeOn;
	
	randomSetupLowerBound = 1;
	randomSetupUpperBound = 9;

	currentSetup=0;		//give it 0 so it never equals randomSetup the 1st time

	colors = {
			{230/255.0, 0/255.0, 0/255.0},	//special vehicle red

			{0/255.0, 0/255.0, 230/255.0},

			{230/255.0, 230/255.0, 0/255.0},
			{230/255.0, 0/255.0, 230/255.0},
			{0/255.0, 230/255.0, 230/255.0},

			{15/255.0, 155/255.0, 30/255.0 },
			{168/255.0, 208/255.0, 141/255.0},
			{249/255.0, 151/255.0, 43/255.0},
			{255/255.0, 51/255.0, 153/255.0},
			{0/255.0, 176/255.0, 240/255.0},
			{177/255.0, 126/255.0, 216/255.0},
			{90/255.0, 125/255.0, 218/255.0},
			{102/255.0, 0/255.0, 204/255.0},

			{0/255.0, 90/255.0, 0/255.0},
			{90/255.0, 0/255.0, 0/255.0},
			{0/255.0, 0/255.0, 90/255.0},
			};

	movesMessage = "Moves: ";
	statusMessage = "Game Playing";

	newGame();
}

void Game::createGame(){
	metrics.setMoveCount(0);	//reset score since this is called in restart() & newGame()
	theSetup = GameSetup(currentSetup);		//get a setup by number from whatever the current setup number is

	//Empty Board is already set up
	//GameSetup constructor created a layout, use it to populate the board
	selectedVehicleIndex=0;		//choose the 0th item in vectorOfVehicles (the SpecialVehicle)
	populateBoard(theSetup.getSetupAsList());
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

void Game::setDebugPrintVehicleLocations(bool printBoard){
	if(printBoard){
		for(int i=0; i<vectorOfVehicles.size(); i++){
			vectorOfVehicles[i]->setDebugPrintBoard(true);
		}
	}
	else{
		for(int i=0; i<vectorOfVehicles.size(); i++){
			vectorOfVehicles[i]->setDebugPrintBoard(false);
		}
	}
}


void Game::setSelectedVehicleIndex(int vehicleIndex) {
	selectedVehicleIndex=vehicleIndex;
}

int Game::getSelectedVehicleIndex() const{
	return selectedVehicleIndex;
}

unique_ptr<Vehicle> const& Game::getSelectedVehicle() const {
	return vectorOfVehicles[selectedVehicleIndex];
}

vector<unique_ptr<Vehicle>> const& Game::getVehicles() const {
	return vectorOfVehicles;
}

ScoreMetrics& Game::getMetrics(){
	return metrics;
}

string Game::getStatusMessage() const {
	return statusMessage;
}

void Game::setStatusMessage(string message) {
	statusMessage = message;
}

Button& Game::getSaveButton(){
	return saveButton;
}

Button& Game::getLoadButton(){
	return loadButton;
}

Button& Game::getRestartButton(){
	return restartButton;
}

Button& Game::getNewGameButton(){
	return newGameButton;
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

	setVehicleColors();
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

		int oldSetup;
		inputFile >> oldSetup;		//Now the 1st number in the vector is which setup 
		fileContents.erase(fileContents.begin());	//erase the setup number leaving a valid setup vector for populateBoard
		currentSetup = oldSetup;

		populateBoard(fileContents);
	}
	else{
		setStatusMessage("There was no game saved");
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
	allVehicleInfo = allVehicleInfo + to_string(currentMoveCount) + "\n";		//add 2 newlines after to differentiate from vehicle info
	allVehicleInfo = allVehicleInfo + to_string(currentSetup) + "\n\n";		//add which setup it is

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
	int currentSetupLength = to_string(currentSetup).length();
	int newLineCount = 3;	//1 ater writing currentMoveCount & 2 more after currentSetup
	int vehicleInfStringOffset = currentMoveCountLength + currentSetupLength + newLineCount;		//how many characters in de we insert the data for horizontalCount & verticalCount

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

void Game::newGame(){
	//Pick a random setup, but remember the current one and choose a number that's different
	int randomSetup = GameSetup::getRandomInt(randomSetupLowerBound, randomSetupUpperBound);
	while(randomSetup == currentSetup){
		randomSetup = GameSetup::getRandomInt(randomSetupLowerBound, randomSetupUpperBound);
	}
	currentSetup=randomSetup;	//update change the current setup
	createGame();
}

void Game::restart(){
	createGame();		//rebuilds the game using the current setup
}

void Game::draw() const{
	board.draw();
	for(int i=0; i<vectorOfVehicles.size(); i++){
		vectorOfVehicles[i]->draw();
	}
	drawButtons();
	drawInstructions();
	drawMoves();
	drawTextLarge(getStatusMessage(), statusMessageX, statusMessageY);	//draw status message
}

void Game::drawButtons() const{
	saveButton.draw();
	loadButton.draw();
	restartButton.draw();
	newGameButton.draw();
}

void Game::drawInstructions() const{
	int lineHeight = 15;
	vector<string> instructions = { "Rush Hour", "Save the red car from the traffic jam", "Click to select a Car", "Arrow keys to move"};
	for(int i=0; i<instructions.size(); i++){
		drawTextMedium(instructions[i], statusMessageX, buttonY+buttonHeight  +lineHeight*(i+1));
	}
	
}

void Game::drawMoves() const{
	glColor3f(0, 0, 0);
	int moves = metrics.getMoveCount();		//get the current score
	string moveOutput = movesMessage + to_string(moves);	//concatenate the label with the actual number
	//Position 2 square from the left of the board, & 1/2 the square size above the top of the board
	glRasterPos2i(SQUARE_UPPER_LEFT_X + SQUARE_SIZE*2, SQUARE_UPPER_LEFT_Y - SQUARE_SIZE/2.0);
	for (int i = 0; i < moveOutput.length(); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, moveOutput[i]);
	}
}

void Game::setVehicleColors(){
	for(int i=0; i<vectorOfVehicles.size(); i++){
		vectorOfVehicles[i]->setInitialColor(colors[i]);
		vectorOfVehicles[i]->setColor(colors[i]);
	}
}