#include "GlobalWindowPositions.h"

int GlobalWindowPositions::borderSize = 6;
int GlobalWindowPositions::upperCornerX = 50 +borderSize;
int GlobalWindowPositions::upperCornerY = 50 +borderSize;
int GlobalWindowPositions::squareSize = 50;
int GlobalWindowPositions::squareSizeMinusBorder = squareSize - borderSize;
int GlobalWindowPositions::boardPixelSpan = 6 * squareSize +borderSize;	//make containing background square that's as big as the squares inside, but also accounts for the border

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

int GlobalWindowPositions::getBoardPixelSpan() const {
	return boardPixelSpan;
}