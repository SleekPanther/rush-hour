#ifndef graphics_h
#define graphics_h

#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <string>

using namespace std;


struct Color {
	double red;
	double green;
	double blue;
};


//Constants for pixel size, positions, brightness adjustments
static const double MAX_COLOR_VALUE = 255;		//colors go from 0 to 255
static const double HOVER_PERCENT_CHANGE = 30;	//how much to brighten/darken a color
static const double HOVER_CLICK_PERCENT_CHANGE = 60;	//how much to brighten/darken a color

static const Color textColor = {0, 0, 0};

static const int SQUARE_SIZE = 50;
static const int BORDER_SIZE = 6;
static const int SQUARE_SIZE_MINUS_BORDER = SQUARE_SIZE - BORDER_SIZE;
static const int BOARD_WIDTH = 6 * SQUARE_SIZE +BORDER_SIZE;

static const int BOARD_UPPER_LEFT_X = 50;
static const int BOARD_UPPER_LEFT_Y = 50;
static const int SQUARE_UPPER_LEFT_X = BOARD_UPPER_LEFT_X +BORDER_SIZE;
static const int SQUARE_UPPER_LEFT_Y = BOARD_UPPER_LEFT_Y +BORDER_SIZE;

static const int VEHICLE_UPPER_LEFT_X = SQUARE_UPPER_LEFT_X - BORDER_SIZE/2.0;	//divide by 2 to center in middle of border
static const int VEHICLE_UPPER_LEFT_Y = SQUARE_UPPER_LEFT_Y - BORDER_SIZE/2.0;	//divide by 2 to center in middle of border

static const int buttonSpacing = 5;
static const int buttonX = 50;
static const int buttonY = 400;
static const int buttonHeight = 30;
static const int saveButtonWidth = 40;
static const int loadButtonX = buttonX + saveButtonWidth +buttonSpacing;
static const int loadButtonWidth = 40;
static const int restartButtonX = loadButtonX + loadButtonWidth +buttonSpacing;
static const int restartButtonWidth = 50;
static const int newGameButtonX = restartButtonX + restartButtonWidth +buttonSpacing;
static const int newGameButtonWidth = 70;

static const int statusMessageX = buttonX;
static const int statusMessageY = buttonY + 130;


//Lightens an input color by adding adding to red, green & blue components & returns a new color
Color lightenColor(Color color, double rgbIncrease);

//draw text on screen at a specific location
void drawTextLarge(string text, int x, int y);

void drawTextMedium(string text, int x, int y);


// Program initialization NOT OpenGL/GLUT dependent, as we haven't created a GLUT window yet
void init(void);

//Display different things based on the GameState
void displayGameBegin();

void displayGameEnd();


// Callback functions for GLUT

// Draw the window - this is where all the GL actions are
void display(void);

// Called when window is resized, also when window is first created, before the first call to display()
void reshape(int w, int h);

// Refresh the display, called when system is idle
void refresh(void);

// Trap and process keyboard events
void keyboard(unsigned char key, int x, int y);

// Process modifier/special keys
void keyboardSpecial(unsigned char key, int x, int y);

// Handle "mouse cursor moved" events 
void cursor(int x, int y);

//Handle mouse click events
void mouse(int button, int state, int x, int y);

// Handle "mouse moved with button pressed" events
void drag(int x, int y);

//For glutTimerFunc
void timer(int extra);


//initialize glut & OpenGL & register callback functions
void runGame(int argc, char** argv);


#endif