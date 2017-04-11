#include "Board.hpp"

Board::Board() {
	cout << "\tNew board" << endl;
	minXCoord = 0;
	maxXCoord = 6;
	minYCoord = 0;
	maxYCoord = 6;

	occupiedSquares = {
		{false, false, false, false, false, false},
		{false, false, false, false, false, false},
		{false, false, false, false, false, false},
		{false, false, false, false, false, false},
		{false, false, false, false, false, false},
		{false, false, false, false, false, false}
	};
}

Board::~Board() {
}

int Board::getMinXCoord() const {
	return minXCoord;
}

int Board::getMaxXCoord() const {
	return maxXCoord;
}

int Board::getMinYCoord() const {
	return minYCoord;
}

int Board::getMaxYCoord() const {
	return maxYCoord;
}

bool Board::isUnoccupiedSpace(Coordinate2D coordinate) {
	return !occupiedSquares[coordinate.x][coordinate.y];	//negate the value from grid since want to return if the is UN-occupied
}
