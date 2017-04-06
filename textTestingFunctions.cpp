#include "textTestingFunctions.hpp"

void runAllTests() {
	
	if (test_Game()) {
		cout << "Passed test_Game() tests" << endl;
	}
	cout << endl << endl;

	if (test_Vehicle()) {
		cout << "Passed test_Vehicle() tests" << endl;
	}


}

bool test_Game() {
	bool passed = true;

	Game game;

	return passed;
}

bool test_Vehicle() {
	bool passed = true;

	//create vehicle, test it & return set passed = false if anything fails

	return passed;
}
