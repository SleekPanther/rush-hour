#include "graphics.h"
#include "textTestingFunctions.h"

GLdouble windowWidth, windowHeight;
int window;
int mouseXPosition;		//cursor function updates these positions
int mouseYPosition;


enum class GameState {menu, playing, won};
GameState currentGameState;

Game game;

Color lightenColor(Color color, double percentToLighten){
	double red= color.red + percentToLighten/maxColorValue;
	double green = color.green + percentToLighten/maxColorValue;
	double blue = color.blue + percentToLighten/maxColorValue;
	return Color{red, green, blue };
}

void init() {
	windowWidth = 500;
	windowHeight = 500;

	currentGameState=GameState::playing;
	// currentGameState=GameState::menu;

	// game.setDebugPrintVehicleLocations(true);
}

void displayMenu() {
	string message = "Click anywhere to begin";
	glColor3f(1, 1, 1);
	glRasterPos2i(100, 250);
	for (int i = 0; i < message.length(); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
	}
}

void displayGameBegin() {
	game.draw();
}

void displayGameEnd() {
	string message = "Game Ended";
	glColor3f(1, 1, 0);
	glRasterPos2i(100, 250);
	for (int i = 0; i < message.length(); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
	}
}

void displayGameSave() {

}


// Initialize OpenGL Graphics
void initGL() {
	// Set "clearing" or background color
	glClearColor(0.7f, 0.7f, 0.0f, 1.0f);
}

// Handler for window-repaint event. Call back when the window first appears and whenever the window needs to be re-painted.
void display() {
	glViewport(0, 0, windowWidth, windowHeight);	// tell OpenGL to use the whole window for drawing
	
	// do an orthographic parallel projection with the coordinate system set to first quadrant, limited by screen/window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, windowWidth, windowHeight, 0.0, -1.f, 1.f);
	

	glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//draw shapes no matter what (ignores order in which a rectangle is drawn)

	if (currentGameState == GameState::menu) {
		displayMenu();
	}else if (currentGameState == GameState::playing) {
		displayGameBegin();
	}if (currentGameState == GameState::won) {
		displayGameEnd();
	}
	
	glFlush();	// Render now
}

void reshape(int w, int h){
}

void refresh(void){
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void keyboard(unsigned char key, int x, int y) {
	if (key == 27) {	// escape
		glutDestroyWindow(window);
		exit(0);
	}
	
	glutPostRedisplay();
	
	return;
}

void keyboardSpecial(int key, int x, int y) {
	if(currentGameState==GameState::playing) {
		if(key==GLUT_KEY_DOWN){
				if(game.getSelectedVehicle()->moveDown()){
					game.getMetrics().increaseMoveCount();
				}
			}
		else if(key==GLUT_KEY_LEFT){
				if(game.getSelectedVehicle()->moveLeft()){
					game.getMetrics().increaseMoveCount();
				}
			}
		else if(key==GLUT_KEY_RIGHT){
			if(!game.getSelectedVehicle()->isInWinningSpace()){		//only move if the game isn't over
				if(game.getSelectedVehicle()->moveRight()){
					game.getMetrics().increaseMoveCount();
				}
			}
			
			if(game.getSelectedVehicle()->isInWinningSpace()){	//Check if that move made them win the game
				currentGameState= GameState::won;
			}
		}
		else if(key==GLUT_KEY_UP){
				if(game.getSelectedVehicle()->moveUp()){
					game.getMetrics().increaseMoveCount();
				}
			}
	}
	else if(currentGameState==GameState::won){
		cout << "Game is over, can't move\n";
	}

	cout << "Movecount = " << game.getMetrics().getMoveCount() << "\n";
	
	glutPostRedisplay();
}

void cursor(int x, int y) {
	mouseXPosition = x;
	mouseYPosition = y;

	if(currentGameState == GameState::playing){
		//Loop over all vehicles & check if the cursor overlaps with any of them
		for(int i=0; i<game.getVehicles().size(); i++){
			if(i != game.getSelectedVehicleIndex()) {
				if(game.getVehicles()[i]->isOverlapping(x, y)){
					Color initialColor = game.getVehicles()[i]->getInitialColor();
					game.getVehicles()[i]->setColor(lightenColor(initialColor, HOVER_PERCENT_CHANGE));
				}
				else{
					game.getVehicles()[i]->setColor( game.getVehicles()[i]->getInitialColor() );
				}
			}
		}
	}
	glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
	if(currentGameState == GameState::menu){
		currentGameState = GameState:: playing;
	}
	else if(currentGameState == GameState::playing){
		if(state==GLUT_DOWN){	//only register clicks, not releases
			cout << "Mouse clicked (" << x << ", " << y << ")\n";

			//Loop over vehicles to see if mouse actually clicked any of them
			for(int i=0; i<game.getVehicles().size(); i++){
				if(game.getVehicles()[i]->isOverlapping(x, y)){	//if point is inside the vehicle boundary
					game.setSelectedVehicleIndex(i);		//we found a vehicle that was clicked, so update to be the vehicle to be moved
					Color initialColor = game.getVehicles()[i]->getInitialColor();
					game.getVehicles()[i]->setColor(lightenColor(initialColor, HOVER_CLICK_PERCENT_CHANGE));
				}
			}
		}
	}
	else if(currentGameState == GameState::won){
		//click button to restart
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
	
	glutInitWindowSize((int)windowWidth, (int)windowHeight);
	glutInitWindowPosition(100, 100); // Position the window's initial top-left corner

	window = glutCreateWindow("Rush Hour");		// create the window and store the handle to it
	
	// Register callback handler for window re-paint event
	glutDisplayFunc(display);

	initGL();	// Our own OpenGL initialization
	
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