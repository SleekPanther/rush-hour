#include "Board.h"

Board::Board() {
	winningSpace = Coordinate2D(6, 2);		//row index 3, column index 7  is the 1 free space in the board boundary to win the game. Listed here as a vehicle coordinate (hence the intentional off-by-one mismatch)
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

	borderSize = globalPositions.getBorderSize();
	upperCornerX = globalPositions.getUpperCornerX();
	upperCornerY = globalPositions.getUpperCornerY();
	boardUpperCornerX = upperCornerX -borderSize;
	boardUpperCornerY = upperCornerY -borderSize;
	squareSize = globalPositions.getSquareSize();
	squareSizeMinusBorder = globalPositions.getSquareSizeMinusBorder();

	borderColor = {0, 0, 0};
	squareColor = {0, 1, 0};
}

Board::~Board() {
}

vector<vector<bool>> Board::getOccupiedSquares() const{
	return occupiedSquares;
}

Coordinate2D Board::getWinningSpace() const{
	return winningSpace;
}

bool Board::isWinningSpace(int x, int y) const{
	return (x == winningSpace.x) && (y == winningSpace.y);
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


void Board::draw() const{
	//draw board background container (acts as the border because inner squares are drawn smaller to give the illusion of a border)
	glBegin(GL_QUADS);
	glColor3f(borderColor.red, borderColor.green, borderColor.blue);
	int boardPixelSpan = (occupiedSquares.size()-2) * squareSize +borderSize;	//make containing background square that's as big as the squares inside, but also accounts for the border
	glVertex2i(boardUpperCornerX, boardUpperCornerY);		//top left
	glVertex2i(boardUpperCornerX + boardPixelSpan, boardUpperCornerY);		//top right
	glVertex2i(boardUpperCornerX + boardPixelSpan, boardUpperCornerY + boardPixelSpan);	//bottom right
	glVertex2i(boardUpperCornerX, boardUpperCornerY + boardPixelSpan);		//bottom left
	glEnd();

	//draw grid square 	DRAWS VERTICAL COLUMNS TOP TO BOTTOM, THEN COLUMNS LEFT TO RIGHT
	int rowAndColumnCount = occupiedSquares.size()-2;		//-2 since 8X8 grid & only draw 6X6
	for(int i=0; i<rowAndColumnCount; i++){		//i controls how many columns are drawn, x values (left to right)
		for(int j=0; j<rowAndColumnCount; j++){		//j controls how many rows in a column, y values (top to bottom)
			glBegin(GL_QUADS);
			glColor3f(1, 1, 1);
			// cout << "tl ("<<(upperCornerX +squareSize*i)<<", "<<(upperCornerY +squareSize*j) <<")";
			glVertex2i(upperCornerX +squareSize*i, upperCornerY +squareSize*j);		//top left
			// cout << "\ttr ("<<(upperCornerX + squareSizeMinusBorder +squareSize*i)<<", "<< (upperCornerY +squareSize*j ) << ")";
			glVertex2i(upperCornerX + squareSizeMinusBorder +squareSize*i, upperCornerY +squareSize*j);		//top right
			// cout << "\t\tbr ("<<(upperCornerX + squareSizeMinusBorder +squareSize*i)<<", "<<(upperCornerY+squareSizeMinusBorder + squareSize*j)<<")";
			glVertex2i(upperCornerX + squareSizeMinusBorder +squareSize*i, upperCornerY+squareSizeMinusBorder + squareSize*j);		//bottom right
			// cout << "\tbl ("<<(upperCornerX +squareSize*i)<<", "<<(upperCornerY+squareSizeMinusBorder +squareSize*j ) <<")\n";
			glVertex2i(upperCornerX +squareSize*i, upperCornerY+squareSizeMinusBorder +squareSize*j);		//bottom left
			glEnd();
		}
	}
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