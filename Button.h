#ifndef Button_hpp
#define Button_hpp

#include "graphics.h"

using namespace std;

class Button{
private:
	int height;		//dimensions of a rectangle
	int width;
	int upperLeftX;
	int upperLeftY;
	int leftTextPadding;	//Buttons are inside rectangles, but give some padding to the left
	Color initialColor;		//base color that hover color change is based on
	Color color;	//the actual color seen when drawing
	string text;

public:
	Button(int width, int height, int upperLeftX, int upperLeftY, string text, Color color);

	Color getColor() const;

	void setColor(Color color);

	// Requires: nothing
	// Modifies: nothing
	// Effects: checks if a point is inside the rectangle boundary
	bool isOverlapping(int x, int y) const;

	void draw() const;
};

#endif