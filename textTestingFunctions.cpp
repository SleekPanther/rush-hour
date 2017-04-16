#include "textTestingFunctions.hpp"

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
	cout << endl << endl;
}

bool test_Game() {
	bool passed = true;

	Game game;

	return passed;
}

bool test_GameSetup() {
	bool passed = true;

	GameSetup setup;

	return passed;
}

bool test_Board() {
	bool passed = true;

	Board board;
	cout << "Printing board occupied squares\n" << board << endl;

	int upperLeftX =0;
	int upperLeftY =0;
	if(!board.isUnoccupiedSpace(upperLeftX, upperLeftY)){
		cout << "Failed new board, then board.isUnoccupiedSpace(" << upperLeftX << ", " <<upperLeftY << "). Expected true, Returned " << board.isUnoccupiedSpace(upperLeftX, upperLeftY) << endl;
		passed=false;
	}
	int upperLeftBoundaryX =-1;				//check the actual board, since isUnoccupiedSpace() adjusts for vehicle coordinates
	int upperLeftBoundaryY =-1;
	if(board.isUnoccupiedSpace(upperLeftBoundaryX, upperLeftBoundaryY)){
		cout << "Failed new board, then board.isUnoccupiedSpace(" << upperLeftBoundaryX << ", " <<upperLeftBoundaryY << "). Expected false, Returned " << board.isUnoccupiedSpace(upperLeftBoundaryX, upperLeftBoundaryY) << endl;
		passed=false;
	}

	int centerIshSpaceX = 2;
	int centerIshSpaceY = 3;
	if(!board.isUnoccupiedSpace(centerIshSpaceX, centerIshSpaceY)){
		cout << "Failed new board, then board.isUnoccupiedSpace(" << centerIshSpaceX << ", " <<centerIshSpaceY << "). Expected true, Returned " << board.isUnoccupiedSpace(centerIshSpaceX, centerIshSpaceY) << endl;
		passed=false;
	}

	int winningX = board.getWinningSpace().x;	//these are from the vehicle's perspective, getOccupiedSquares() checks 1 greater than these
	int winningY = board.getWinningSpace().y;
	//The actual winning space is [3][7] in the 2D vector. Adjusted here by subtracting 1 from both x & y since isUnoccupiedSpace() adds 1
	//and reversed x & y coordinates so it can be accessed (x, y),  not (y, x) like vectors do
	if(!board.isUnoccupiedSpace(winningX, winningY)){
		cout << "Failed new board, then board.isUnoccupiedSpace(" << winningX << ", " <<winningY << "). Expected true, Returned " << board.isUnoccupiedSpace(winningX, winningY) << endl;
		passed=false;
	}


	if(!board.isWinningSpace(winningX, winningY)){
		cout << "Failed new board, then board.isWinningSpace(" << winningX << ", " <<winningY << "). Expected true, Returned " << board.isWinningSpace(winningX, winningY) << endl;
		passed=false;
	}

	int nonWinningX = board.getWinningSpace().x -1;		//Check some other square to make sure it's not the winning space
	int nonWinningY = board.getWinningSpace().y -1;
	if(board.isWinningSpace(nonWinningX, nonWinningY)){
		cout << "Failed new board, then board.isWinningSpace(" << nonWinningX << ", " <<nonWinningY << "). Expected false, Returned " << board.isWinningSpace(nonWinningX, nonWinningY) << endl;
		passed=false;
	}

	return passed;
}

bool test_Coordinate2D() {
	bool passed = true;

	Coordinate2D coordinate;
	if(coordinate.x != 0 || coordinate.y !=0){
		cout << "Failed creating default Coordinate2D. Expected coordinate.x==0, Returned " << coordinate.x << " Expected coordinate.y==0, Returned " << coordinate.y << endl;
		passed=false;
	}

	int test1X=10;
	int test1Y=3;
	Coordinate2D coordinate2(test1X, test1Y);
	if(coordinate2.x != test1X || coordinate2.y !=test1Y){
		cout << "Failed creating Coordinate2D with 2-arg constructor. Expected coordinate2.x==" << test1X <<", Returned " << coordinate2.x << " Expected coordinate.y=="<< test1Y <<", Returned " << coordinate2.y << endl;
		passed=false;
	}


	int test2X = 3;
	int test2Y = 2;
	coordinate2.setCoordinate(test2X, test2Y);
	if(coordinate2.x != test2X || coordinate2.y !=test2Y){
		cout << "Failed setCoordinate(" << test2X << ", " << test2Y << "). Expected coordinate2.x==" << test2X <<", Returned " << coordinate2.x << ",  Expected coordinate.y=="<< test2Y <<", Returned " << coordinate2.y << endl;
		passed=false;
	}

	Coordinate2D testCoord = coordinate2.getCoordinateObject();
	if(testCoord.x != coordinate2.x || testCoord.y != coordinate2.y){
		cout << "Failed Coordinate2D testCoord = coordinate2.getCoordinateObject(). Expected testCoord.x==" << coordinate2.x <<", Returned " << testCoord.x << ",  Expected coordinate.y=="<< coordinate2.y <<", Returned " << testCoord.y << endl;
		passed=false;
	}


	cout << "Print Coordinate2D with overloaded << operator: " << testCoord << endl;

	return passed;
}

bool test_Vehicle() {
	bool passed = true;


	vector<unique_ptr<Vehicle>> vehicles;
	Coordinate2D inputCoordsCoord1(2, 2);
	Coordinate2D inputCoordsCoord2(2, 3);
	vector<Coordinate2D> inputCoords = {inputCoordsCoord1, inputCoordsCoord2};
	vector<Coordinate2D> inputCoords2 = {Coordinate2D(5, 5), Coordinate2D(5, 4)};
	vector<Coordinate2D> inputCoords3 = {Coordinate2D(3, 0), Coordinate2D(4, 0)};
	Board testBoard;
	vehicles.push_back(make_unique<HorizontalVehicle>(testBoard, inputCoords));
	vehicles.push_back(make_unique<HorizontalVehicle>(testBoard, inputCoords2));
	vehicles.push_back(make_unique<VerticalVehicle>(testBoard, inputCoords3));

	if(vehicles[0]->isInWinningSpace()){	//default vehicle should not be placed in winning space
		cout << "Failed creating a vehicle with coordinates " << inputCoordsCoord1 << ", " << inputCoordsCoord2 << " Expecting isInWinningSpace() false, returned " << vehicles[0]->isInWinningSpace() << endl;
		passed=false;
	}

	vector<Coordinate2D> coords = vehicles[0]->getCoordinates();

	// cout << "Test Printing vehicles[0] coordinates (horizontal vehicle)" << endl;
	// vehicles[0]->printCoordinates();

	cout << "Board populated with vehicles before any movement \n" << testBoard << endl;
	if(vehicles[0]->moveLeft()){
		cout << "Successfully moved left" << endl;
	}
	else{
		cout << "Failed to move left" << endl;
	}
	cout << "Coordinates of vehicles[0] after moveLeft()" << endl;
	vehicles[0]->printCoordinates();
 
	if(vehicles[0]->moveLeft()){
		cout << "Successfully moved left" << endl;
	}
	else{
		cout << "Failed to move left" << endl;
	}
	cout << "Coordinates of vehicles[0] after moveLeft()" << endl;
	vehicles[0]->printCoordinates();

	//move left again (should fail since hits left wall)
	if(vehicles[0]->moveLeft()){
		cout << "Successfully moved left" << endl;
	}
	else{
		cout << "Cannot to move left" << endl;
	}
	cout << "Coordinates of vehicles[0] after moveLeft()" << endl;
	vehicles[0]->printCoordinates();

	
	// for (int i = 0; i < vehicles.size(); i++) {
	// 	// vehicles[i]->
	// }

	return passed;
}

bool test_ScoreMetrics() {
	bool passed = true;

	ScoreMetrics metrics;

	return passed;
}