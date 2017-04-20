#include "SpecialVehicle.h"

SpecialVehicle::SpecialVehicle(Board & board, vector<Coordinate2D> coordinates): HorizontalVehicle(board, coordinates) {
}

SpecialVehicle::~SpecialVehicle() {
}

bool SpecialVehicle::moveRight() {
	bool canMove = true;

	vacateBoard();		//temporarily remove vehicle from board to check new coordinates
	//check all potential new coordinates & verify they're legal moves into unoccupied spaces
	for(int i=0; i<coordinates.size(); i++){
		int newXCoord = coordinates[i].x + 1;	//new position where the vehicle ideally wants to go
		//SpecialVehicle modifies the move method to check if it won the game
		if(board.isWinningSpace(newXCoord, coordinates[i].y)){		//This should only happen for 1 coordinate, & there should never be a conflict with the winningSpace being occupied
			inWinningSpace=true;
		}
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