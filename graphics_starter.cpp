#include "graphics.hpp"
#include "textTestingFunctions.h"

enum screen_state {menu, game_begin, game_save, game_end};

GLdouble width, height;
int wd;
screen_state screen;

void display_menu() {
    string message = "Click anywhere to begin";
    glColor3f(1, 1, 1);
    glRasterPos2i(100, 250);
    for (int i = 0; i < message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
}

void display_game_begin() {

}

void display_game_end() {
    // draw a string message
    string message = "Game Ended";
    glColor3f(1, 1, 0);
    glRasterPos2i(100, 250);
    for (int i = 0; i < message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
}

void display_game_save() {

}



void init() {
	width = 500;
	height = 500;
	
	screen = menu;
}

/* Initialize OpenGL Graphics */
void initGL() {
	// Set "clearing" or background color
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
	// tell OpenGL to use the whole window for drawing
	glViewport(0, 0, width, height);
	
	// do an orthographic parallel projection with the coordinate
	// system set to first quadrant, limited by screen/window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, -1.f, 1.f);
	

	
	glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	switch(screen) {
        case menu:
            display_menu();
            break;
        case game_begin:
            display_game_begin();
            break;
        case game_end:
            display_game_over();
            break;
	case game_save:
            display_game_save();
            break;		
        }

	
	glFlush();  // Render now
}

void reshape(int w, int h){
}

void refresh(void){
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void keyboard(unsigned char key, int x, int y) {
	// escape
	if (key == 27) {
		glutDestroyWindow(wd);
		exit(0);
	}
	
	glutPostRedisplay();
	
	return;
}

void keyboardSpecial(int key, int x, int y) {
	if (screen == game_begin) {
	switch(key) {
		case GLUT_KEY_DOWN:
			
			break;
		case GLUT_KEY_LEFT:
			
			break;
		case GLUT_KEY_RIGHT:
			
			break;
		case GLUT_KEY_UP:
			
			break;
	    }
        }
	
	glutPostRedisplay();
}

void cursor(int x, int y) {
	if (screen == game_begin) {
		
		
	
		
		
		
		
		
	}
	glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && screen == menu) {
              screen = game_begin;
         }
	
	
	glutPostRedisplay();
}

void drag(int x, int y){
}

void timer(int extra) {
	
	glutPostRedisplay();
	glutTimerFunc(30, timer, 0);
}

void runGame(int argc, char** argv){
	init();
	
	glutInit(&argc, argv);          // Initialize GLUT
	
	glutInitDisplayMode(GLUT_RGBA);
	
	glutInitWindowSize((int)width, (int)height);
	glutInitWindowPosition(100, 100); // Position the window's initial top-left corner
	/* create the window and store the handle to it */
	wd = glutCreateWindow("Fun with Drawing!" /* title */ );
	
	// Register callback handler for window re-paint event
	glutDisplayFunc(display);
	
	// Our own OpenGL initialization
	initGL();
	
	// register keyboard press event processing function
	// works for numbers, letters, spacebar, etc.
	glutKeyboardFunc(keyboard);
	
	// register special event: function keys, arrows, etc.
	glutSpecialFunc(keyboardSpecial);
	
	// handles mouse movement
	glutPassiveMotionFunc(cursor);
	
	// handles mouse click
	glutMouseFunc(mouse);
	
	// handles timer
	glutTimerFunc(0, timer, 0);
	
	// Enter the event-processing loop
	glutMainLoop();
}

//Main function: GLUT runs as a console application starting at main()
int main(int argc, char** argv) {
	cout << "Enter 1 to play, 0 to test: ";
	int choice;
	//cin >> choice;
	choice = 1;
	if(choice==0){		//testing mode
		cout << boolalpha;
		runAllTests();

		cout << "\n\nUser testing load/save\n";
		chooseLoadSave();
	}
	else{
		runGame(argc, argv);
	}

	return 0;
}
