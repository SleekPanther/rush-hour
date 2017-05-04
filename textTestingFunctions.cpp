#include "textTestingFunctions.h"


void runAllTests() {
	if (test_Game()) {
		cout << "Passed test_Game() tests" << endl;
	}
	cout << endl << endl;

	if (test_GameSetup()) {
		cout << "Passed test_GameSetup() tests" << endl;
	}
	cout << endl << endl;

	if (test_Board()) {
		cout << "Passed test_Board() tests" << endl;
	}
	cout << endl << endl;

	if (test_Coordinate2D()) {
		cout << "Passed test_Coordinate2D() tests" << endl;
	}
	cout << endl << endl;

	if (test_Vehicle()) {
		cout << "Passed test_Vehicle() tests" << endl;
	}
	cout << endl << endl;

	if (test_ScoreMetrics()) {
		cout << "Passed test_ScoreMetrics() tests" << endl;
	}
}

bool test_Game() {
	cout << "\n**Begin test_Game() tests**\n" << endl;

	bool passed = true;

	Game game(true);

	game.setDebugPrintProgressFile(true);
	if(!game.getDebugPrintProgressFile()){
		cout << "Failed consturcting new game, game.setDebugPrintProgressFile(true) then game.getDebugPrintProgressFile(). Expected true, returned false" << endl;
		passed=false;
	}
	game.setDebugPrintProgressFile(false);
	if(game.getDebugPrintProgressFile()){
		cout << "Failed consturcting new game, game.setDebugPrintProgressFile(false) then game.getDebugPrintProgressFile(). Expected false, returned true" << endl;
		passed=false;
	}

	game.setDebugPrintPopulateBoard(true);
	if(!game.getDebugPrintPopulateBoard()){
		cout << "Failed consturcting new game, game.setDebugPrintPopulateBoard(true) then game.getDebugPrintPopulateBoard(). Expected true, returned false" << endl;
		passed=false;
	}
	game.setDebugPrintPopulateBoard(false);
	if(game.getDebugPrintPopulateBoard()){
		cout << "Failed consturcting new game, game.setDebugPrintPopulateBoard(false) then game.getDebugPrintPopulateBoard(). Expected false, returned true" << endl;
		passed=false;
	}

	cout << "\nTesting game.load()\n";
	game.load();

	//game.save() is tested in test_Vehicle() since we add vehicles to the board

	return passed;
}

bool test_GameSetup() {
	cout << "\n**Begin test_GameSetup() tests**\n\n";
	bool passed = true;

	GameSetup setup;

	string testFilename = "setup01.txt";
	cout << "Testing reading from \"" << testFilename <<"\" & placing in vector " << endl;
	vector<int> fileContents = GameSetup::readFile(testFilename);
	GameSetup::printVector(fileContents);

	vector<int> testNumbers = {1, 2, 3};
	cout << "Testing GameSetup::printVector() on {1, 2, 3}. Expecting \"1, 2, 3, \"  function returns:\n" ;
	GameSetup::printVector(testNumbers);

	int randomNumber=0;
	int lowerBound =0;
	int upperBound=5;
	for(int i=0; i<20; i++){
		randomNumber = GameSetup::getRandomInt(lowerBound, upperBound);
		if(randomNumber<(lowerBound)){
			cout << "Failed random number generation. lowerBound=" << lowerBound << ", Random number=" << randomNumber << ",  " << randomNumber << "<" << lowerBound << endl;
			passed=false;
		}
		else if(randomNumber>upperBound){
			cout << "Failed random number generation. upperBound=" << upperBound << ", Random number=" << randomNumber << ",  " << randomNumber << ">" << upperBound << endl;
			passed=false;
		}
	}
	
	return passed;
}

bool test_Board() {
	cout << "\n**Begin test_Board() tests**\n" << endl;

	bool passed = true;

	Board board;
	cout << "Printing board occupied squares\n" << board << endl;

	int upperLeftX = 0;
	int upperLeftY = 0;
	if (!board.isUnoccupiedSpace(upperLeftX, upperLeftY)) {
		cout << "Failed new board, then board.isUnoccupiedSpace(" << upperLeftX << ", " << upperLeftY << "). Expected true, Returned " << board.isUnoccupiedSpace(upperLeftX, upperLeftY) << endl;
		passed = false;
	}
	int upperLeftBoundaryX = -1;				//check the actual board, since isUnoccupiedSpace() adjusts for vehicle coordinates
	int upperLeftBoundaryY = -1;
	if (board.isUnoccupiedSpace(upperLeftBoundaryX, upperLeftBoundaryY)) {
		cout << "Failed new board, then board.isUnoccupiedSpace(" << upperLeftBoundaryX << ", " << upperLeftBoundaryY << "). Expected false, Returned " << board.isUnoccupiedSpace(upperLeftBoundaryX, upperLeftBoundaryY) << endl;
		passed = false;
	}

	int centerIshSpaceX = 2;
	int centerIshSpaceY = 3;
	if (!board.isUnoccupiedSpace(centerIshSpaceX, centerIshSpaceY)) {
		cout << "Failed new board, then board.isUnoccupiedSpace(" << centerIshSpaceX << ", " << centerIshSpaceY << "). Expected true, Returned " << board.isUnoccupiedSpace(centerIshSpaceX, centerIshSpaceY) << endl;
		passed = false;
	}

	int winningX = board.getWinningSpace().x;	//these are from the vehicle's perspective, getOccupiedSquares() checks 1 greater than these
	int winningY = board.getWinningSpace().y;
	//The actual winning space is [3][7] in the 2D vector. Adjusted here by subtracting 1 from both x & y since isUnoccupiedSpace() adds 1
	//and reversed x & y coordinates so it can be accessed (x, y),  not (y, x) like vectors do
	if (!board.isUnoccupiedSpace(winningX, winningY)) {
		cout << "Failed new board, then board.isUnoccupiedSpace(" << winningX << ", " << winningY << "). Expected true, Returned " << board.isUnoccupiedSpace(winningX, winningY) << endl;
		passed = false;
	}


	if (!board.isWinningSpace(winningX, winningY)) {
		cout << "Failed new board, then board.isWinningSpace(" << winningX << ", " << winningY << "). Expected true, Returned " << board.isWinningSpace(winningX, winningY) << endl;
		passed = false;
	}

	int nonWinningX = board.getWinningSpace().x - 1;		//Check some other square to make sure it's not the winning space
	int nonWinningY = board.getWinningSpace().y - 1;
	if (board.isWinningSpace(nonWinningX, nonWinningY)) {
		cout << "Failed new board, then board.isWinningSpace(" << nonWinningX << ", " << nonWinningY << "). Expected false, Returned " << board.isWinningSpace(nonWinningX, nonWinningY) << endl;
		passed = false;
	}


	board.setSquareOccupied(2, 3);
	if (board.isUnoccupiedSpace(2, 3)) {
		cout << "Failed new board, boad.setSquareOccupied(2, 3), then board.isUnoccupiedSpace(2, 3). Expected false, Returned " << board.isUnoccupiedSpace(2, 3) << endl;
		passed = false;
	}

	board.setSquareVacant(2, 3);		//Clear the space
	if (!board.isUnoccupiedSpace(2, 3)) {
		cout << "Failed new board, boad.setSquareVacant(2, 3), then board.isUnoccupiedSpace(2, 3). Expected true, Returned " << board.isUnoccupiedSpace(2, 3) << endl;
		passed = false;
	}

	return passed;
}

bool test_Coordinate2D() {
	cout << "\n**Begin test_Coordinate2D() tests**\n" << endl;

	bool passed = true;

	Coordinate2D coordinate;
	if (coordinate.x != 0 || coordinate.y != 0) {
		cout << "Failed creating default Coordinate2D. Expected coordinate.x==0, Returned " << coordinate.x << " Expected coordinate.y==0, Returned " << coordinate.y << endl;
		passed = false;
	}

	int test1X = 10;
	int test1Y = 3;
	Coordinate2D coordinate2(test1X, test1Y);
	if (coordinate2.x != test1X || coordinate2.y != test1Y) {
		cout << "Failed creating Coordinate2D with 2-arg constructor. Expected coordinate2.x==" << test1X << ", Returned " << coordinate2.x << " Expected coordinate.y==" << test1Y << ", Returned " << coordinate2.y << endl;
		passed = false;
	}


	int test2X = 3;
	int test2Y = 2;
	coordinate2.setCoordinate(test2X, test2Y);
	if (coordinate2.x != test2X || coordinate2.y != test2Y) {
		cout << "Failed setCoordinate(" << test2X << ", " << test2Y << "). Expected coordinate2.x==" << test2X << ", Returned " << coordinate2.x << ",  Expected coordinate.y==" << test2Y << ", Returned " << coordinate2.y << endl;
		passed = false;
	}

	Coordinate2D testCoord = coordinate2.getCoordinateObject();
	if (testCoord.x != coordinate2.x || testCoord.y != coordinate2.y) {
		cout << "Failed Coordinate2D testCoord = coordinate2.getCoordinateObject(). Expected testCoord.x==" << coordinate2.x << ", Returned " << testCoord.x << ",  Expected coordinate.y==" << coordinate2.y << ", Returned " << testCoord.y << endl;
		passed = false;
	}


	cout << "Print Coordinate2D with overloaded << operator: " << testCoord << endl;

	return passed;
}

bool test_Vehicle() {
	cout << "\n**Begin test_Vehicle() tests**\n" << endl;

	bool passed = true;


	Board testBoard;
	vector<unique_ptr<Vehicle>> vehicles;
	
	Coordinate2D inputCoordsCoord1(2, 4);		//used to print where the 1st vehicle is drawn, but not actually used when adding to vector
	Coordinate2D inputCoordsCoord2(3, 4);

	vehicles.push_back(make_unique<HorizontalVehicle>(testBoard, vector<Coordinate2D>{ Coordinate2D(2, 4), Coordinate2D(3, 4)}));
	vehicles.push_back(make_unique<SpecialVehicle>(testBoard, vector<Coordinate2D>{ Coordinate2D(4, 2), Coordinate2D(3, 2)}));
	vehicles.push_back(make_unique<VerticalVehicle>(testBoard, vector<Coordinate2D>{ Coordinate2D(1, 0), Coordinate2D(1, 1)}));

	//For testing, we want to see where the vehicles are on the board
	for(int i=0; i<vehicles.size(); i++){
		vehicles[i]->setDebugPrintBoard(true);
	}


	//Special vehicle is also a horizontal vehicle
	for(int i=0; i< vehicles.size(); i++){
		cout << "vehicle type: " << vehicles[i]->getVehicleType() <<endl;
	}
	cout << "\n\n";


	if (vehicles[0]->isInWinningSpace()) {	//default vehicle should not be placed in winning space
		cout << "Failed creating a vehicle with coordinates " << inputCoordsCoord1 << ", " << inputCoordsCoord2 << " Expecting isInWinningSpace() false, returned " << vehicles[0]->isInWinningSpace() << endl;
		passed = false;
	}

	cout << "Test Printing vehicles[0] coordinates (horizontal vehicle)" << endl;
	vehicles[0]->printCoordinates();


	cout << "Board populated with vehicles before any movement\n" << testBoard << endl;

	//Temporarily remove vehicle from board & make sure it's gone
	vehicles[0]->vacateBoard();
	cout << "Board after vehicles[0] has temporarily vacated \n" << testBoard << endl;
	vector<Coordinate2D> vehicle0Coords = vehicles[0]->getCoordinates();
	for (int i = 0; i<vehicle0Coords.size(); i++) {
		int x = vehicle0Coords[i].x;
		int y = vehicle0Coords[i].y;
		if (!testBoard.isUnoccupiedSpace(x, y)) {
			cout << "Failed vehicles[0] vacating board, then testBoard.isUnoccupiedSpace(" << x << ", " << y << ")  Expected true, returned: " << testBoard.isUnoccupiedSpace(x, y) << endl;
		}
	}

	vehicles[0]->reOccupyBoard();
	cout << "Board after vehicles[0] has re-Occupied the board\n" << testBoard << endl;
	for (int i = 0; i<vehicle0Coords.size(); i++) {
		int x = vehicle0Coords[i].x;
		int y = vehicle0Coords[i].y;
		if (testBoard.isUnoccupiedSpace(x, y)) {
			cout << "Failed vehicles[0] reOccupyBoard board, then testBoard.isUnoccupiedSpace(" << x << ", " << y << ")  Expected false, returned: " << testBoard.isUnoccupiedSpace(x, y) << endl;
		}
	}


	if (vehicles[0]->moveLeft()) {
		cout << "Successfully moved left " << endl;
	}
	else {
		cout << "Failed to move left " << endl;
	}
	cout << '\n';

	if (vehicles[0]->moveLeft()) {
		cout << "Successfully moved left " << endl;
	}
	else {
		cout << "Failed to move left " << endl;
	}
	cout << '\n';

	//move left again (should fail since hits left wall)
	if (vehicles[0]->moveLeft()) {
		cout << "SHOULDN'T have moved left " << endl;
	}
	else {
		cout << "Cannot to move left " << endl;
	}
	cout << '\n';


	if (vehicles[1]->moveRight()) {
		cout << "Successfully moved right " << endl;
	}
	else {
		cout << "Cannot to move right " << endl;
	}
	if (vehicles[1]->isInWinningSpace()) {
		cout << "Failed vehicles[1]->moveRight() then vehicles[1]->isInWinningSpace()  Expected false, returned: " << vehicles[1]->isInWinningSpace() << endl;
		passed = false;
	}
	cout << '\n';

	//Move right again to win the game
	if (vehicles[1]->moveRight()) {
		cout << "Successfully moved right " << endl;
	}
	else {
		cout << "Cannot to move right " << endl;
	}
	if (vehicles[1]->isInWinningSpace()) {
		cout << "vehicles[1] isInWinningSpace, game should end " << endl;
	}
	else {
		cout << "Failed vehicles[1]->moveRight() then vehicles[1]->isInWinningSpace()  Expected true, returned: " << vehicles[1]->isInWinningSpace() << endl;
		passed = false;
	}
	cout << '\n';


	//Check horizontal Vehicles moving up & down
	if (vehicles[0]->moveUp()) {
		cout << "Failed vehicles[0]->moveUp()  Expected false, returned: true" << endl;
		passed = false;
	}
	if (vehicles[0]->moveDown()) {
		cout << "Failed vehicles[0]->moveDown()  Expected false, returned: true" << endl;
		passed = false;
	}

	//Double check for Special Vehicle moveUp / moveDown()
	if (vehicles[1]->moveUp()) {
		cout << "Failed vehicles[1]->moveUp()  Expected false, returned: true" << endl;
		passed = false;
	}
	if (vehicles[1]->moveDown()) {
		cout << "Failed vehicles[1]->moveDown()  Expected false, returned: true" << endl;
		passed = false;
	}


	//TEST VerticalVehicles MOVEMENT
	if (vehicles[2]->moveDown()) {
		cout << "Successfully moved Down " << endl;
	}
	else {
		cout << "Failed to move Down " << endl;
	}
	cout << '\n';

	if (vehicles[2]->moveDown()) {
		cout << "Successfully moved Down " << endl;
	}
	else {
		cout << "Failed to move Down " << endl;
	}
	cout << '\n';

	//Cannot move down any further
	if (vehicles[2]->moveDown()) {
		cout << "SHOULDN'T have moved Down " << endl;
	}
	else {
		cout << "Cannot move Down " << endl;
	}
	cout << '\n';

	//Now Test moveUp
	if (vehicles[2]->moveUp()) {
		cout << "Successfully moved Up " << endl;
	}
	else {
		cout << "Failed to move Up " << endl;
	}
	cout << '\n';


	if (vehicles[2]->moveLeft()) {
		cout << "Failed vehicles[2]->moveLeft()  Expected false, returned: true" << endl;
		passed = false;
	}
	if (vehicles[2]->moveRight()) {
		cout << "Failed vehicles[2]->moveRight()  Expected false, returned: true" << endl;
		passed = false;
	}


	Game game(true);
	cout << "Testing game.save()  Check Progress file for matching contents" << endl;
	game.save();


	return passed;
}

bool test_ScoreMetrics() {
	cout << "\n**Begin test_ScoreMetrics() tests**\n" << endl;

	bool passed = true;

	ScoreMetrics metrics;
	if (metrics.getMoveCount() != 0) {
		cout << "Failed consturcting new ScoreMetrics and metrics.getMoveCount(). Expected 0, Returned: " << metrics.getMoveCount() << endl;
		passed = false;
	}

	int testNumberOfMoves = 10;
	for (int i = 0; i<testNumberOfMoves; i++) {
		metrics.increaseMoveCount();
	}
	if (metrics.getMoveCount() != testNumberOfMoves) {
		cout << "Failed consturcting new ScoreMetrics and metrics.increaseMoveCount() " << testNumberOfMoves << " times. Expected metrics.getMoveCount()== " << testNumberOfMoves << ", Returned: " << metrics.getMoveCount() << endl;
		passed = false;
	}

	metrics.reset();
	if (metrics.getMoveCount() != 0) {
		cout << "Failed metrics.reset()  Expected metrics.getMoveCount()==0, Returned: " << metrics.getMoveCount() << endl;
		passed = false;
	}

	int oldHighScore = 10;
	metrics.setMoveCount(oldHighScore);
	if (metrics.getMoveCount() != oldHighScore) {
		cout << "Failed metrics.setMoveCount(" << oldHighScore << ")  Expected metrics.getMoveCount()==" << oldHighScore << ", Returned: " << metrics.getMoveCount() << endl;
		passed = false;
	}

	return passed;
}

void chooseLoadSave(){
	cout << "New Game started. Enter 1 to start new, 0 to open previous game: ";
	int answer;
	cin >> answer;
	cout << "Default board setup\n";
	Game game(true);
	//new game is default, open old game is the other option
	if(answer==0){
		cout << "Erasing board & Loading previous setup\n";
		game.load("progress-backup.txt");
		cout << "Score was: " << game.getMetrics().getMoveCount() << '\n';
	}

	cout << "Enter 1 to save game: ";
	cin >> answer;
	if(answer==1){
		game.save();
		cout << "Game saved, check \"progress.txt\"\n";
	}
	else{
		cout << "Game Progress erased\n";
	}

}