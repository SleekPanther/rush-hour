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

	return passed;
}

bool test_Coordinate2D() {
	bool passed = true;

	Coordinate2D coordinate;
	if(coordinate.x != 0 || coordinate.y !=0){
		cout << "Failed creating default Coordinate2D. Expected coordinate.x==0, Returned " << coordinate.x << " Expected coordinate.y==0, Returned " << coordinate.y << endl;
		passed=false;
	}

	int testX=10;
	int testY=3;
	Coordinate2D coordinate2(testX, testY);
	if(coordinate2.x != testX || coordinate2.y !=testY){
		cout << "Failed creating Coordinate2D with 2-arg constructor. Expected coordinate2.x==" << testX <<", Returned " << coordinate2.x << " Expected coordinate.y=="<< testY <<", Returned " << coordinate2.y << endl;
		passed=false;
	}

	return passed;
}

bool test_Vehicle() {
	bool passed = true;

	vector<unique_ptr<Vehicle>> vehicles;
	vehicles.push_back(make_unique<HorizontalVehicle>());
	//vehicles.push_back(make_unique<VerticalVehicle>());
	///vehicles.push_back(make_unique<SpecialVehicle>());
	
	for (int i = 0; i < vehicles.size(); i++) {
		// vehicles[i]->
	}

	return passed;
}

bool test_ScoreMetrics() {
	bool passed = true;

	//ScoreMetrics metrics;

	return passed;
}