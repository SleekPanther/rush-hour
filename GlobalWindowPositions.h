#ifndef GlobalWindowPositions_hpp
#define GlobalWindowPositions_hpp

//Simple a collection of global variables accessible by Board & vehicles
class GlobalWindowPositions{
private:
	static int borderSize;
	static int upperCornerX;
	static int upperCornerY;
	static int squareSize;
	static int squareSizeMinusBorder;

public:
	int getBorderSize() const;
	
	int getUpperCornerX() const;
	
	int getUpperCornerY() const;
	
	int getSquareSize() const;

	int getSquareSizeMinusBorder() const;
};

#endif