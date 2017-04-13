#include "Board.hpp"

Board::Board() {
	minXCoord = 0;
	maxXCoord = 6;
	minYCoord = 0;
	maxYCoord = 6;

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

	//all false for testing
	// occupiedSquares = {
	// 	{false, false, false, false, false, false, false, false},
	// 	{false, false, false, false, false, false, false, false},
	// 	{false, false, false, false, false, false, false, false},
	// 	{false, false, false, false, false, false, false, true},	//winning square
	// 	{false, false, false, false, false, false, false, false},
	// 	{false, false, false, false, false, false, false, false},
	// 	{false, false, false, false, false, false, false, false},
	// 	{false, false, false, false, false, false, false, false},
	// };

	//more testing
	// occupiedSquares = {
	// 	{true, true, true, true, true, true, true, true},
	// 	{true, true, true, true, true, true, true, true},
	// 	{true, true, true, true, true, true, true, true},
	// 	{true, true, true, true, true, true, true, false},	//winning square
	// 	{true, true, true, true, true, true, true, true},
	// 	{true, true, true, true, true, true, true, true},
	// 	{true, true, true, true, true, true, true, true},
	// 	{true, true, true, true, true, true, true, true},
	// };
}

Board::~Board() {
}

int Board::getMinXCoord() const {
	return minXCoord;
}

int Board::getMaxXCoord() const {
	return maxXCoord;
}

int Board::getMinYCoord() const {
	return minYCoord;
}

int Board::getMaxYCoord() const {
	return maxYCoord;
}

vector<vector<bool>> Board::getOccupiedSquares() const{
	return occupiedSquares;
}

bool Board::isUnoccupiedSpace(int x, int y) {
	//+1 to x & y since board has a border of occupied squares around the edge making the grid bigger
	return !occupiedSquares[y+1][x+1];	//negate the value from grid since want to return if the is UN-occupied
}

void Board::draw() {
	//draw board on screen
	cout << "Draws board on screen" << endl;
}


ostream& operator << (ostream& outStream, const Board& board){
	vector<vector<bool>> squares= board.getOccupiedSquares();
	for(int i=0; i<squares.size(); i++){
		cout << squares[i][0];		//print 1st item 
		for(int j=1; j<squares[i].size(); j++){
			cout << ", " << squares[i][j];	//print remaining with commas between
		}
		cout << endl;
	}
	return outStream;
}