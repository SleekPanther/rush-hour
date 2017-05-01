#include "GlobalWindowPositions.h"

int GlobalWindowPositions::borderSize = 6;
int GlobalWindowPositions::upperCornerX = 0 +borderSize;
int GlobalWindowPositions::upperCornerY = 0 +borderSize;
int GlobalWindowPositions::squareSize = 50;
int GlobalWindowPositions::squareSizeMinusBorder = squareSize - borderSize;

int GlobalWindowPositions::getBorderSize() const {
	return borderSize;
}

int GlobalWindowPositions::getUpperCornerX() const {
	return upperCornerX;
}

int GlobalWindowPositions::getUpperCornerY() const {
	return upperCornerY;
}

int GlobalWindowPositions::getSquareSize() const {
	return squareSize;
}

int GlobalWindowPositions::getSquareSizeMinusBorder() const {
	return squareSizeMinusBorder;
}