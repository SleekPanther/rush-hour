#include "Vehicle.h"

//board(board) sets the reference in an initializer list. For some reason this cannot happen inside the body
Vehicle::Vehicle(Board & board, vector<Coordinate2D> coordinates) : board(board), coordinates(coordinates), inWinningSpace(false) {
	debugPrintBoard = false;		//initially, vehicles DO NOT display the board after every move

	upCornerX=globalPositions.getUpperCornerX() - globalPositions.getBorderSize()/2.0;	//divide by 2 to center in middle of border
	upCornerY=globalPositions.getUpperCornerY() - globalPositions.getBorderSize()/2.0;	//divide by 2 to center in middle of border
	squareSize=globalPositions.getSquareSize();

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

void Vehicle::setColor(vector<double> rbg){
	color.red=rbg[0];
	color.green=rbg[1];
	color.blue=rbg[2];
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
	glColor3f(color.red, color.green, color.blue);

	int x=0;	//temporary variables to store each coordinate component
	int y=0;
	for(int i=0; i<coordinates.size(); i++){
		x=coordinates[i].x;
		y=coordinates[i].y;

		glBegin(GL_QUADS);
		glVertex2i(upCornerX +squareSize*x,  upCornerY +squareSize*y);		//top left
		glVertex2i(upCornerX+squareSize +squareSize*x,  upCornerY +squareSize*y);		//top right
		glVertex2i(upCornerX+squareSize +squareSize*x,  upCornerY+squareSize +squareSize*y);		//bottom right
		glVertex2i(upCornerX +squareSize*x,  upCornerY+squareSize +squareSize*y);		//bottom left
		glEnd();
	}
}

bool Vehicle::isOverlapping(int mouseX, int mouseY) const {
	bool overlapsWithVehicle = false;	//assume it doesn't overlap

	for(int i=0; i<coordinates.size(); i++){
		int x=coordinates[i].x;
		int y=coordinates[i].y;

		int leftX = upCornerX +squareSize*x;
		int topY = upCornerY +squareSize*y;
		int rightX = upCornerX+squareSize +squareSize*x;
		int bottomY = upCornerY+squareSize +squareSize*y;

		//Check if a point overlaps the square. Stop early if 1 overlap is found
		if( (mouseX>=leftX) && (mouseX<=rightX) && (mouseY>=topY) && (mouseY<=bottomY) ){
			overlapsWithVehicle = true;
			break;
		}
	}
	if(overlapsWithVehicle){
		cout << overlapsWithVehicle << ":  overlapped " << "(" << mouseX << ", " << mouseY << ")\n";
	}
	return overlapsWithVehicle;
}