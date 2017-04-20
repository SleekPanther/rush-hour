#include "HorizontalVehicle.h"

HorizontalVehicle::HorizontalVehicle(Board & board, vector<Coordinate2D> coordinates): Vehicle(board, coordinates) {
}

HorizontalVehicle::~HorizontalVehicle() {
}

//Horizontal Vehicles can only move left or right
bool HorizontalVehicle::moveUp() {
	return false;
}

//Horizontal Vehicles can only move left or right
bool HorizontalVehicle::moveDown() {
	return false;
}

bool HorizontalVehicle::moveLeft() {
	bool canMove = true;

	vacateBoard();		//temporarily remove vehicle from board to check new coordinates
	//check all potential new coordinates & verify they're legal moves into unoccupied spaces
	for(int i=0; i<coordinates.size(); i++){
		int newXCoord = coordinates[i].x - 1;	//new position where the vehicle ideally wants to go
		if( !board.isUnoccupiedSpace(newXCoord, coordinates[i].y) ){	//check if new x coord & old y coordinate space is free
			canMove=false;
			break;
		}
	}
	reOccupyBoard();	//add vehicle back to the board once new positions have been calculated

	if(canMove){		//actually move if all new spaces are valid
		vacateBoard();		//remove its old position from the board
		for(int i=0; i<coordinates.size(); i++){		//calculate new position
			coordinates[i].x = coordinates[i].x - 1;
		}
		reOccupyBoard();		//move to new position by adding to the board
	}
	if(debugPrintBoard){
		cout << "Board after attempted move (from move method)\n" << board;
	}

	return canMove;
}

bool HorizontalVehicle::moveRight() {
	bool canMove = true;

	vacateBoard();		//temporarily remove vehicle from board to check new coordinates
	//check all potential new coordinates & verify they're legal moves into unoccupied spaces
	for(int i=0; i<coordinates.size(); i++){
		int newXCoord = coordinates[i].x + 1;	//new position where the vehicle ideally wants to go
		if( !board.isUnoccupiedSpace(newXCoord, coordinates[i].y) ){	//check if new x coord & old y coordinate space is free
			canMove=false;
			break;
		}
	}
	reOccupyBoard();	//add vehicle back to the board once new positions have been calculated

	if(canMove){		//actually move if all new spaces are valid
		vacateBoard();		//remove its old position from the board
		for(int i=0; i<coordinates.size(); i++){		//calculate new position
			coordinates[i].x = coordinates[i].x + 1;
		}
		reOccupyBoard();		//move to new position by adding to the board
	}
	if(debugPrintBoard){
		cout << "Board after attempted move (from move method)\n" << board;
	}

	return canMove;
}