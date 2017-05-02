#include "Button.h"

Button::Button(int width, int height, int upperLeftX, int upperLeftY, string text, Color color) {
	this->width=width;
	this->height=height;
	this->upperLeftX=upperLeftX;
	this->upperLeftY=upperLeftY;
	this->text=text;
	this->color=color;
}

void Button::setColor(Color color) {
	this->color=color;
}

bool Button::isOverlapping(int x, int y) {
	return false;
}

void Button::draw() const {
	glBegin(GL_QUADS);
	glColor3f(color.red, color.green, color.blue);
	glVertex2i(upperLeftX, upperLeftY);	//top left
	glVertex2i(upperLeftX +width, upperLeftY);	//top right
	glVertex2i(upperLeftX+width, upperLeftY+height);	//bottom right
	glVertex2i(upperLeftX, upperLeftY+height);	//bottom left
	glEnd();
}