#include "Board.h"

Board::Board() {
	winningSpace = Coordinate2D(6, 2);		//3rd row down, 7th column across is the 1 free space in the board boundary to win the game
	occupiedSquares = {
		{true, true, true, true, true, true, true, true},
		{true, false, false, false, false, false, false, true},
		{true, false, false, false, false, false, false, true},
		{true, false, false, false, false, false, false, false},	//winning square on the edge
		{true, false, false, false, false, false, false, true},
		{true, false, false, false, false, false, false, true},
		{true, false, false, false, false, false, false, true},
		{true, true, true, true, true, true, true, true},
	};
}

Board::~Board() {
}

vector<vector<bool>> Board::getOccupiedSquares() const{
	return occupiedSquares;
}

bool Board::isUnoccupiedSpace(int x, int y) const{
	return !getSquareValueFromVehicleCoordinates(x, y);		//negate the value from grid since want to return if the is UN-occupied
}

void Board::setSquareVacant(int x, int y){
	setSquareValueFromVehicleCoordinates(x, y, false);
}

void Board::setSquareOccupied(int x, int y){
	setSquareValueFromVehicleCoordinates(x, y, true);
}

bool Board::getSquareValueFromVehicleCoordinates(int x, int y) const{
	//+1 to x & y since board has a border of occupied squares around the edge making the grid bigger
	return occupiedSquares[y+1][x+1];
}

void Board::setSquareValueFromVehicleCoordinates(int x, int y, bool value){
	//+1 to x & y since board has a border of occupied squares around the edge making the grid bigger
	occupiedSquares[y+1][x+1] = value;
}

Coordinate2D Board::getWinningSpace() const{
	return winningSpace;
}

bool Board::isWinningSpace(int x, int y) const{
	return (x == winningSpace.x) && (y == winningSpace.y);
}

void Board::draw() {
	//draw board itself
	//then loop through vehicles & draw
	//don't need to worry about order of drawing vehicles since they can't overlap
	cout << "Draws board on screen" << endl;
}


ostream& operator << (ostream& outStream, const Board& board){
	vector<vector<bool>> squares= board.getOccupiedSquares();
	for(int i=0; i<squares.size(); i++){
		cout << squares[i][0];		//print 1st item 
		for(int j=1; j<squares[i].size(); j++){
			cout << " \t" << squares[i][j];		//print remaining with space between
		}
		cout << endl;
	}
	return outStream;
}