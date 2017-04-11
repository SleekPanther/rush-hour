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

	//might not these, if occupiedSquares can take care of everything
	int getMinXCoord() const;
	int getMaxXCoord() const;
	int getMinYCoord() const;
	int getMaxYCoord() const;

	vector<vector<bool>> getOccupiedSquares() const;

	// Requires: coordinate with x & y components inside valid board dimensions
	// Modifies: nothing
	// Effects: tells you if space is free. Takes in a Coordinate2D so that we don't confuse x & y of the coordiante with x & y of the vector (which are (y, x))
	bool isUnoccupiedSpace(int x, int y);


	friend ostream& operator << (ostream& outStream, const Board& board);
};

#endif