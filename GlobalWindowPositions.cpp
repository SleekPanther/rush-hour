#include "GlobalWindowPositions.h"

int GlobalWindowPositions::upperCornerX = 50;
int GlobalWindowPositions::upperCornerY = 50;
int GlobalWindowPositions::squareSize = 50;
int GlobalWindowPositions::borderSize = 6;
int GlobalWindowPositions::squareSizeMinusBorder = squareSize - borderSize;

int GlobalWindowPositions::getUpperCornerX() const {
	return upperCornerX;
}

int GlobalWindowPositions::getUpperCornerY() const {
	return upperCornerY;
}

int GlobalWindowPositions::getSquareSize() const {
	return squareSize;
}

int GlobalWindowPositions::getBorderSize() const {
	return borderSize;
}

int GlobalWindowPositions::getSquareSizeMinusBorder() const {
	return squareSizeMinusBorder;
}