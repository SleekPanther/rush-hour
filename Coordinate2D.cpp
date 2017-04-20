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

ostream& operator << (ostream& outStream, const Coordinate2D& coordinate){
	cout << "(" << coordinate.x << ", " << coordinate.y << ")";
	return outStream;
}