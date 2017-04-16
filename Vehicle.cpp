#include "Vehicle.hpp"

//board(board) sets the reference in an initializer list. For some reason this cannot happen inside the body
Vehicle::Vehicle(Board & board, vector<Coordinate2D> coordinates) : board(board), coordinates(coordinates), inWinningSpace(false) {
	debugPrintBoard=true;		//change this to not the board when not testing
	for(int i=0; i<coordinates.size(); i++){
		board.setSquareOccupied(coordinates[i].x, coordinates[i].y);	//set new position to be occupied
	}
}

Vehicle::~Vehicle() {
}

vector<Coordinate2D> Vehicle::getCoordinates() const {
	return coordinates;
}

int Vehicle::getLength() const{
	return coordinates.size();
}

void Vehicle::printCoordinates() const {
	cout << "Vehicle Coordinates:" << endl;
	for (int i = 0; i < coordinates.size(); i++) {
		cout << coordinates[i] << endl;
	}
}

void Vehicle::vacateBoard(){
	for(int i=0; i<coordinates.size(); i++){
		board.setSquareVacant(coordinates[i].x, coordinates[i].y);
	}
}

void Vehicle::reOccupyBoard(){
	for(int i=0; i<coordinates.size(); i++){
		board.setSquareOccupied(coordinates[i].x, coordinates[i].y);
	}
}

bool Vehicle::isInWinningSpace() const{
	return inWinningSpace;
}

void Vehicle::draw(){
	//loop through vector of coordinates & draw vehicle based on that location
}