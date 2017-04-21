#include "Vehicle.h"

//board(board) sets the reference in an initializer list. For some reason this cannot happen inside the body
Vehicle::Vehicle(Board & board, vector<Coordinate2D> coordinates) : board(board), coordinates(coordinates), inWinningSpace(false) {
	debugPrintBoard = false;		//initially, vehicles DO NOT display the board after every move
	for (int i = 0; i<coordinates.size(); i++) {
		board.setSquareOccupied(coordinates[i].x, coordinates[i].y);	//set new position to be occupied
	}
}

Vehicle::~Vehicle() {
}

void Vehicle::setDebugPrintBoard(bool debugPrintBoardOn){
	debugPrintBoard=debugPrintBoardOn;
}

bool Vehicle::getDebugPrintBoard() const{
	return debugPrintBoard;
}

vector<Coordinate2D> Vehicle::getCoordinates() const {
	return coordinates;
}

int Vehicle::getLength() const {
	return coordinates.size();
}

string Vehicle::getStringCoordinates() const {
	string coordString = "Vehicle Coordinates: ";
	for (int i = 0; i < coordinates.size(); i++) {
		coordString = coordString + coordinates[i].toString() + "  ";
	}
	return coordString;
}

void Vehicle::printCoordinates() const {
	cout << getStringCoordinates() << '\n';
}

void Vehicle::printBoardAndCoordinatesIfDebug() const {
	if(debugPrintBoard){
		cout << "Board after attempted move (from move method)\n" << board;
		cout << "Vehicle coordinates after move: " << getStringCoordinates() << '\n';
	}
}

void Vehicle::vacateBoard() {
	for (int i = 0; i<coordinates.size(); i++) {
		board.setSquareVacant(coordinates[i].x, coordinates[i].y);
	}
}

void Vehicle::reOccupyBoard() {
	for (int i = 0; i<coordinates.size(); i++) {
		board.setSquareOccupied(coordinates[i].x, coordinates[i].y);
	}
}

bool Vehicle::isInWinningSpace() const {
	return inWinningSpace;
}

void Vehicle::draw() {
	//loop through vector of coordinates & draw vehicle based on that location
}