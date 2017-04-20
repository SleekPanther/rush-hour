#ifndef Coordinate2D_h
#define Coordinate2D_h

#include <iostream>

using namespace std;

//This is basiaclly a struct, but a class with public fields to allow easier overloaded operators

class Coordinate2D {
public:
	int x;		//public fields, like struct
	int y;

	// constructor sets default point to (0, 0)
	Coordinate2D();

	//2-arg sets x & y to input x & y's
	Coordinate2D(int x, int y);

	// Requires: nothing
	// Modifies: nothing
	// Effects: returns coordinate
	Coordinate2D getCoordinateObject() const;
	
	// Requires: x & y > 0 & less than 6 (the board dimensions)
	// Modifies: x & y
	// Effects: updates fields with input parameters
	void setCoordinate(int x, int y);


	friend ostream& operator << (ostream& outStream, const Coordinate2D& coordinate);
};

#endif
