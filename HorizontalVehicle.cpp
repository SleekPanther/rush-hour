#include "HorizontalVehicle.hpp"

HorizontalVehicle::HorizontalVehicle(Board & board, vector<Coordinate2D> coordinates): Vehicle(board, coordinates) {
}

HorizontalVehicle::~HorizontalVehicle() {
}

bool HorizontalVehicle::moveUp() {
	return false;
}

bool HorizontalVehicle::moveDown() {
	return false;
}

bool HorizontalVehicle::moveLeft() {
	bool canMove = true;

	//check all potential new coordinates & verify they're legal moves into unoccupied spaces
	for(int i=0; i<coordinates.size(); i++){
		int newXCoord = coordinates[i].x - 1;	//where the vehicle ideally wants to go
		if( !board.isUnoccupiedSpace(newXCoord, coordinates[i].y) ){	//check if new x coord & old y coordinate space is free
			canMove=false;
			break;
		}
	}

	if(canMove){		//actually move if all new spaces are valid
		for(int i=0; i<coordinates.size(); i++){
			board.setSquareVacant(coordinates[i].x, coordinates[i].y);		//remove its old position before moving
			coordinates[i].x = coordinates[i].x - 1;				//actually move
			board.setSquareOccupied(coordinates[i].x, coordinates[i].y);	//set new position to be occupied
		}
	}
	if(debugPrintBoard){
		cout << "Board after attempted move (in move method)\n" << board << endl;
	}

	return canMove;
}

bool HorizontalVehicle::moveRight() {
	//change functionality
	return true;
}