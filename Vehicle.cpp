#include "Vehicle.hpp"

Vehicle::Vehicle() {
}

Vehicle::Vehicle(vector<Coordinate2D> coordinates) : coordinates(coordinates) {
}

Vehicle::~Vehicle() {
}

vector<Coordinate2D> Vehicle::getCoordinates() const {
	return coordinates;
}
