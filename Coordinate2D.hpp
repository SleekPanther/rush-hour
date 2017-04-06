#ifndef Coordinate2D_hpp
#define Coordinate2D_hpp

struct Coordinate2D {
	int x;
	int y;

	// constructor sets default point to (0, 0)
	Coordinate2D(): x(0), y(0){
	}

	//2-arg sets x & y to input x & y's
	Coordinate2D(int x, int y): x(x), y(y){
	}
};

#endif