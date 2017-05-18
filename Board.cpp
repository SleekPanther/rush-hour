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

	squareSize = globalPositions.getSquareSize();
	squareSizeMinusBorder = globalPositions.getSquareSizeMinusBorder();
	boardPixelSpan = globalPositions.getBoardPixelSpan();	//make containing background square that's as big as the squares inside, but also accounts for the border

	exitSquareUpperLeftX = BOARD_UPPER_LEFT_X + boardPixelSpan;
	exitSquareUpperLeftY = SQUARE_UPPER_LEFT_Y +squareSize*2;

	exitSquareWidth = squareSize*2;


	exitMessage = "Exit";

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
	glVertex2i(BOARD_UPPER_LEFT_X, BOARD_UPPER_LEFT_Y);		//top left
	glVertex2i(BOARD_UPPER_LEFT_X + boardPixelSpan, BOARD_UPPER_LEFT_Y);		//top right
	glVertex2i(BOARD_UPPER_LEFT_X + boardPixelSpan, BOARD_UPPER_LEFT_Y + boardPixelSpan);	//bottom right
	glVertex2i(BOARD_UPPER_LEFT_X, BOARD_UPPER_LEFT_Y + boardPixelSpan);		//bottom left
	glEnd();

	//draw grid square 	DRAWS VERTICAL COLUMNS TOP TO BOTTOM, THEN COLUMNS LEFT TO RIGHT
	int rowAndColumnCount = occupiedSquares.size()-2;		//-2 since 8X8 grid & only draw 6X6
	for(int i=0; i<rowAndColumnCount; i++){		//i controls how many columns are drawn, x values (left to right)
		for(int j=0; j<rowAndColumnCount; j++){		//j controls how many rows in a column, y values (top to bottom)
			glBegin(GL_QUADS);
			glColor3f(1, 1, 1);
			// cout << "tl ("<<(SQUARE_UPPER_LEFT_X +squareSize*i)<<", "<<(SQUARE_UPPER_LEFT_Y +squareSize*j) <<")";
			glVertex2i(SQUARE_UPPER_LEFT_X +squareSize*i, SQUARE_UPPER_LEFT_Y +squareSize*j);		//top left
			// cout << "\ttr ("<<(SQUARE_UPPER_LEFT_X + squareSizeMinusBorder +squareSize*i)<<", "<< (SQUARE_UPPER_LEFT_Y +squareSize*j ) << ")";
			glVertex2i(SQUARE_UPPER_LEFT_X + squareSizeMinusBorder +squareSize*i, SQUARE_UPPER_LEFT_Y +squareSize*j);		//top right
			// cout << "\t\tbr ("<<(SQUARE_UPPER_LEFT_X + squareSizeMinusBorder +squareSize*i)<<", "<<(SQUARE_UPPER_LEFT_Y+squareSizeMinusBorder + squareSize*j)<<")";
			glVertex2i(SQUARE_UPPER_LEFT_X + squareSizeMinusBorder +squareSize*i, SQUARE_UPPER_LEFT_Y+squareSizeMinusBorder + squareSize*j);		//bottom right
			// cout << "\tbl ("<<(SQUARE_UPPER_LEFT_X +squareSize*i)<<", "<<(SQUARE_UPPER_LEFT_Y+squareSizeMinusBorder +squareSize*j ) <<")\n";
			glVertex2i(SQUARE_UPPER_LEFT_X +squareSize*i, SQUARE_UPPER_LEFT_Y+squareSizeMinusBorder +squareSize*j);		//bottom left
			glEnd();
		}
	}

	drawExitSquare();
}

void Board::drawExitSquare() const{
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex2i(exitSquareUpperLeftX, exitSquareUpperLeftY);	//top left
	glVertex2i(exitSquareUpperLeftX +exitSquareWidth, exitSquareUpperLeftY);	//top right
	glVertex2i(exitSquareUpperLeftX +exitSquareWidth, exitSquareUpperLeftY +squareSizeMinusBorder);	//bottom right
	glVertex2i(exitSquareUpperLeftX, exitSquareUpperLeftY +squareSizeMinusBorder);	//bottom left
	glEnd();

	glColor3f(0, 0, 0);
	glRasterPos2i(exitSquareUpperLeftX +BORDER_SIZE, exitSquareUpperLeftY+squareSize/2.0);
	for (int i = 0; i < exitMessage.length(); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, exitMessage[i]);
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