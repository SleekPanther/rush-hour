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

static const double maxColorValue = 255;		//colors go from 0 to 255
static const double HOVER_PERCENT_CHANGE = 30;	//how much to brighten/darken a color
static const double HOVER_CLICK_PERCENT_CHANGE = 60;	//how much to brighten/darken a color

static const int buttonX = 50;
static const int buttonY = 370;
static const int buttonHeight = 30;

static const int statusMessageX = buttonX;
static const int statusMessageY = 500;

//Lightens an input color by x percent & returns a new color
Color lightenColor(Color color, double percentToLighten);

//draw text on screen at a location
void drawTextLarge(string text, int x, int y);

void drawTextMedium(string text, int x, int y);


// Program initialization NOT OpenGL/GLUT dependent,
// as we haven't created a GLUT window yet
void init(void);

// Callback functions for GLUT */

// Draw the window - this is where all the GL actions are
void display(void);

// Called when window is resized,
// also when window is first created,
// before the first call to display().
void reshape(int w, int h);

// Refresh the display, called when system is idle
void refresh(void);

// Trap and process keyboard events
void keyboard(unsigned char key, int x, int y);

// Process modifier/special keys
void keyboardSpecial(unsigned char key, int x, int y);

// Handle "mouse cursor moved" events 
void cursor(int x, int y);

//handle mouse click events
void mouse(int button, int state, int x, int y);

// Handle "mouse moved with button pressed" events
void drag(int x, int y);

//for glutTimerFunc
void timer(int extra);


//initialize glut & OpenGL & register callback functions
void runGame(int argc, char** argv);


#endif