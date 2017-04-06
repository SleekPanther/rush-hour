#include "VerticalVehicle.hpp"

VerticalVehicle::VerticalVehicle() {
	cout << "\tnew vertical vehicle" << endl;
}

VerticalVehicle::~VerticalVehicle() {
}

bool VerticalVehicle::moveUp() {
	//overrides & actually moves
	return true;
}

bool VerticalVehicle::moveDown() {
	//overrides & actually moves
	return true;
}

bool VerticalVehicle::moveLeft() {
	return false;
}

bool VerticalVehicle::moveRight() {
	return false;
}