#include "Vehicle.h"

//board(board) sets the reference in an initializer list. For some reason this cannot happen inside the body
Vehicle::Vehicle(Board & board, vector<Coordinate2D> coordinates) : board(board), coordinates(coordinates), inWinningSpace(false) {
	debugPrintBoard = false;		//initially, vehicles DO NOT display the board after every move
	colorGlowState = VehicleGlowState::lightening;

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

void Vehicle::setColor(Color newColor){
	color=newColor;
}

Color Vehicle::getColor() const{
	return color;
}

void Vehicle::setInitialColor(vector<double> rbg){
	initialColor.red = rbg[0];
	initialColor.green = rbg[1];
	initialColor.blue = rbg[2];
}

Color Vehicle::getInitialColor() const{
	return initialColor;
}

bool Vehicle::isColorMaxed() const{
	if(getColor().red >= 1.0 || getColor().green >= 1.0 || getColor().blue >= 1.0){
		return true;
	}
	return false;
}

bool Vehicle::isColorInitial() const{
	if(getColor().red <= getInitialColor().red || getColor().green <= getInitialColor().green || getColor().blue <= getInitialColor().blue){
		return true;
	}
	return false;
}

bool Vehicle::shouldLighten() const{
	if(colorGlowState == VehicleGlowState::lightening){
		return true;
	}
	return false;
}

bool Vehicle::shouldDarken() const{
	if(colorGlowState == VehicleGlowState::darkening){
		return true;
	}
	return false;
}

void Vehicle::setLighten(){
	colorGlowState = VehicleGlowState::lightening;
}

void Vehicle::setDarken(){
	colorGlowState = VehicleGlowState::darkening;
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
		glVertex2i(VEHICLE_UPPER_LEFT_X +SQUARE_SIZE*x,  VEHICLE_UPPER_LEFT_Y +SQUARE_SIZE*y);		//top left
		glVertex2i(VEHICLE_UPPER_LEFT_X+SQUARE_SIZE +SQUARE_SIZE*x,  VEHICLE_UPPER_LEFT_Y +SQUARE_SIZE*y);		//top right
		glVertex2i(VEHICLE_UPPER_LEFT_X+SQUARE_SIZE +SQUARE_SIZE*x,  VEHICLE_UPPER_LEFT_Y+SQUARE_SIZE +SQUARE_SIZE*y);		//bottom right
		glVertex2i(VEHICLE_UPPER_LEFT_X +SQUARE_SIZE*x,  VEHICLE_UPPER_LEFT_Y+SQUARE_SIZE +SQUARE_SIZE*y);		//bottom left
		glEnd();
	}
}

bool Vehicle::isOverlapping(int mouseX, int mouseY) const {
	bool overlapsWithVehicle = false;	//assume it doesn't overlap

	for(int i=0; i<coordinates.size(); i++){
		int x=coordinates[i].x;
		int y=coordinates[i].y;

		int leftX = VEHICLE_UPPER_LEFT_X +SQUARE_SIZE*x;
		int topY = VEHICLE_UPPER_LEFT_Y +SQUARE_SIZE*y;
		int rightX = VEHICLE_UPPER_LEFT_X+SQUARE_SIZE +SQUARE_SIZE*x;
		int bottomY = VEHICLE_UPPER_LEFT_Y+SQUARE_SIZE +SQUARE_SIZE*y;

		//Check if a point overlaps the square. Stop early if 1 overlap is found
		if( (mouseX>=leftX) && (mouseX<=rightX) && (mouseY>=topY) && (mouseY<=bottomY) ){	//x between left/right edges & y between to & bottom edges
			overlapsWithVehicle = true;
			break;
		}
	}
	return overlapsWithVehicle;
}