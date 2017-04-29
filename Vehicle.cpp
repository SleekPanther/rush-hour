#include "Vehicle.h"

//board(board) sets the reference in an initializer list. For some reason this cannot happen inside the body
Vehicle::Vehicle(Board & board, vector<Coordinate2D> coordinates) : board(board), coordinates(coordinates), inWinningSpace(false) {
	debugPrintBoard = false;		//initially, vehicles DO NOT display the board after every move
	for (int i = 0; i<coordinates.size(); i++) {
		board.setSquareOccupied(coordinates[i].x, coordinates[i].y);	//set new position to be occupied
	}
}

Vehicle::~Vehicle() {
}

void Vehicle::setDebugPrintBoard(bool debugPrintBoardOn){
	debugPrintBoard=debugPrintBoardOn;
}

bool Vehicle::getDebugPrintBoard() const{
	return debugPrintBoard;
}

vector<Coordinate2D> Vehicle::getCoordinates() const {
	return coordinates;
}

int Vehicle::getLength() const {
	return coordinates.size();
}

string Vehicle::getStringCoordinates() const {
	string coordString = "Vehicle Coordinates: ";
	for (int i = 0; i < coordinates.size(); i++) {
		coordString = coordString + coordinates[i].toString() + "  ";
	}
	return coordString;
}

void Vehicle::printCoordinates() const {
	cout << getStringCoordinates() << '\n';
}

void Vehicle::printBoardAndCoordinatesIfDebug() const {
	if(debugPrintBoard){
		cout << "Board after attempted move (from move method)\n" << board;
		cout << "Vehicle coordinates after move: " << getStringCoordinates() << '\n';
	}
}

void Vehicle::vacateBoard() {
	for (int i = 0; i<coordinates.size(); i++) {
		board.setSquareVacant(coordinates[i].x, coordinates[i].y);
	}
}

void Vehicle::reOccupyBoard() {
	for (int i = 0; i<coordinates.size(); i++) {
		board.setSquareOccupied(coordinates[i].x, coordinates[i].y);
	}
}

bool Vehicle::isInWinningSpace() const {
	return inWinningSpace;
}

void Vehicle::draw() const{
	int x=0;	//temporary variables to store each coordinate component
	int y=0;
	int upCornerX=globalPositions.getUpperCornerX();
	int upCornerY=globalPositions.getUpperCornerY();
	int squareSize=globalPositions.getSquareSize();
	for(int i=0; i<coordinates.size(); i++){
		x=coordinates[i].x;
		y=coordinates[i].y;

		glColor3f(1, 1, 0);
		glBegin(GL_QUADS);
		
		glVertex2i(upCornerX +squareSize*x,  upCornerY +squareSize*y);		//top left
		glVertex2i(upCornerX+squareSize +squareSize*x,  upCornerY +squareSize*y);		//top right
		glVertex2i(upCornerX+squareSize +squareSize*x,  upCornerY+squareSize +squareSize*y);		//bottom right
		glVertex2i(upCornerX +squareSize*x,  upCornerY+squareSize +squareSize*y);		//bottom left
		glEnd();
	}
}

bool Vehicle::isOverlapping(int x, int y) const {
	//Need to check if (x, y) point is inside the vehicle boundary
	return false;
}