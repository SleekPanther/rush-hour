#ifndef Button_hpp
#define Button_hpp

#include "graphics.h"

using namespace std;

class Button{
private:
	int height;
	int width;
	int upperLeftX;
	int upperLeftY;
	Color initialColor;
	Color color;
	string text;

public:
	Button(int width, int height, int upperLeftX, int upperLeftY, string text, Color color);

	Color getColor() const;

	void setColor(Color color);

	bool isOverlapping(int x, int y);

	void draw() const;
};

#endif