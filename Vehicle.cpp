#include "Vehicle.hpp"

Vehicle::Vehicle() {
}

Vehicle::Vehicle(Board board, vector<Coordinate2D> coordinates) : board(board), coordinates(coordinates) {
}

Vehicle::~Vehicle() {
}

vector<Coordinate2D> Vehicle::getCoordinates() const {
	return coordinates;
}

void Vehicle::printCoordinates() const {
	cout << "Vehicle Coordinates:" << endl;
	for (int i = 0; i < coordinates.size(); i++) {
		cout << coordinates[i] << endl;
	}
}
