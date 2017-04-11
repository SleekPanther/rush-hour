#ifndef Board_hpp
#define Board_hpp

#include <iostream>
#include <string>
#include <vector>
#include "Coordinate2D.hpp"

using namespace std;

class Board {
private:
	int minXCoord;
	int maxXCoord;
	int minYCoord;
	int maxYCoord;

	vector<vector<bool>> occupiedSquares;

public:
	Board();
	~Board();

	int getMinXCoord() const;
	int getMaxXCoord() const;
	int getMinYCoord() const;
	int getMaxYCoord() const;

	bool isUnoccupiedSpace(Coordinate2D coordinate);
};

#endif