#include "VerticalVehicle.hpp"

VerticalVehicle::VerticalVehicle(Board & board, vector<Coordinate2D> coordinates): Vehicle(board, coordinates) {
}

VerticalVehicle::~VerticalVehicle() {
}

bool VerticalVehicle::moveUp() {
	bool canMove = true;

	vacateBoard();		//temporarily remove vehicle from board to check new coordinates
	//check all potential new coordinates & verify they're legal moves into unoccupied spaces
	for(int i=0; i<coordinates.size(); i++){
		int newYCoord = coordinates[i].y - 1;	//new position where the vehicle ideally wants to go
		if( !board.isUnoccupiedSpace(coordinates[i].x, newYCoord) ){	//check if new x coord & old y coordinate space is free
			canMove=false;
			break;
		}
	}
	reOccupyBoard();	//add vehicle back to the board once new positions have been calculated

	if(canMove){		//actually move if all new spaces are valid
		vacateBoard();		//remove its old position from the board
		for(int i=0; i<coordinates.size(); i++){		//calculate new position
			coordinates[i].y = coordinates[i].y - 1;
		}
		reOccupyBoard();		//move to new position by adding to the board
	}
	if(debugPrintBoard){
		cout << "Board after attempted move (in move method)\n" << board;
	}

	return canMove;
}

bool VerticalVehicle::moveDown() {
	bool canMove = true;

	vacateBoard();		//temporarily remove vehicle from board to check new coordinates
	//check all potential new coordinates & verify they're legal moves into unoccupied spaces
	for(int i=0; i<coordinates.size(); i++){
		int newYCoord = coordinates[i].y + 1;	//new position where the vehicle ideally wants to go
		if( !board.isUnoccupiedSpace(coordinates[i].x, newYCoord) ){	//check if new x coord & old y coordinate space is free
			canMove=false;
			break;
		}
	}
	reOccupyBoard();	//add vehicle back to the board once new positions have been calculated

	if(canMove){		//actually move if all new spaces are valid
		vacateBoard();		//remove its old position from the board
		for(int i=0; i<coordinates.size(); i++){		//calculate new position
			coordinates[i].y = coordinates[i].y + 1;
		}
		reOccupyBoard();		//move to new position by adding to the board
	}
	if(debugPrintBoard){
		cout << "Board after attempted move (in move method)\n" << board;
	}

	return canMove;
}

//VerticalVehicle can only move up & down
bool VerticalVehicle::moveLeft() {
	return false;
}

//VerticalVehicle can only move up & down
bool VerticalVehicle::moveRight() {
	return false;
}