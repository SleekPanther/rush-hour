#include "HorizontalVehicle.hpp"

HorizontalVehicle::HorizontalVehicle() {
	cout << "\tnew horizontal vehicle" << endl;
}

HorizontalVehicle::~HorizontalVehicle() {
}

bool HorizontalVehicle::moveUp() {
	return false;
}

bool HorizontalVehicle::moveDown() {
	return false;
}

bool HorizontalVehicle::moveLeft() {
	//change functionality
	return true;
}

bool HorizontalVehicle::moveRight() {
	//change functionality
	return true;
}