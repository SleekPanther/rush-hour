#ifndef GlobalWindowPositions_hpp
#define GlobalWindowPositions_hpp

//Simple a collection of global variables accessible by Board & vehicles
class GlobalWindowPositions{
private:
	static int borderSize;		//done
	static int upperCornerX;		//i think done
	static int upperCornerY;		//i think done
	static int squareSize;		//done
	static int squareSizeMinusBorder;
	static int boardPixelSpan;

public:
	int getBorderSize() const;
	
	int getUpperCornerX() const;
	
	int getUpperCornerY() const;
	
	int getSquareSize() const;

	int getSquareSizeMinusBorder() const;

	int getBoardPixelSpan() const;
};

#endif