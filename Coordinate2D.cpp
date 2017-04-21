#include "Coordinate2D.h"

Coordinate2D::Coordinate2D(): x(0), y(0){
}

Coordinate2D::Coordinate2D(int x, int y): x(x), y(y){
}

Coordinate2D Coordinate2D::getCoordinateObject() const {
	return *this;
}

void Coordinate2D::setCoordinate(int x, int y) {
	this->x = x;
	this->y = y;
}

string Coordinate2D::toString() const{
	string coordString = "";
	return coordString + "(" + to_string(this->x) + ", " + to_string(this->y) + ")";
}

ostream& operator << (ostream& outStream, const Coordinate2D& coordinate){
	cout << coordinate.toString();
	return outStream;
}