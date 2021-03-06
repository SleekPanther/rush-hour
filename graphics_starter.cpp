#include "graphics.h"
#include "textTestingFunctions.h"

GLdouble windowWidth, windowHeight;
int window;
int mouseXPosition;		//cursor function updates these positions
int mouseYPosition;


enum class GameState {menu, playing, won};
GameState currentGameState;		//Keep track of the game's state, what buttons work & what to display

Game game;	//Global game object where most interactions take place


Color lightenColor(Color color, double rgbIncrease){
	double red = color.red + rgbIncrease/MAX_COLOR_VALUE;	//add 
	double green = color.green + rgbIncrease/MAX_COLOR_VALUE;
	double blue = color.blue + rgbIncrease/MAX_COLOR_VALUE;
	return Color{red, green, blue };
}

void drawTextLarge(string text, int x, int y){
	glColor3f(textColor.red, textColor.green, textColor.blue);
	glRasterPos2i(x, y);
	for (int i = 0; i < text.length(); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
}

void drawTextMedium(string text, int x, int y){
	glColor3f(textColor.red, textColor.green, textColor.blue);
	glRasterPos2i(x, y);
	for (int i = 0; i < text.length(); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}
}

void init() {
	windowWidth = 500;
	windowHeight = 600;
	currentGameState=GameState::playing;
}

void displayGameBegin() {
	game.draw();
}

void displayGameEnd() {
	game.setStatusMessage("You win! Click Restart or New Game");
	game.draw();
}


// Initialize OpenGL Graphics
void initGL() {
	glClearColor(0.7f, 0.7f, 0.0f, 1.0f);	// Set "clearing" or background color
}

// Handler for window-repaint event. Call back when the window first appears and whenever the window needs to be re-painted.
void display() {
	glViewport(0, 0, windowWidth, windowHeight);	// tell OpenGL to use the whole window for drawing
	
	// do an orthographic parallel projection with the coordinate system set to first quadrant, limited by screen/window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, windowWidth, windowHeight, 0.0, -1.f, 1.f);

	glClear(GL_COLOR_BUFFER_BIT);	// Clear the color buffer with current clearing color
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//draw shapes no matter what (ignores order in which a rectangle is drawn)

	if (currentGameState == GameState::playing) {
		displayGameBegin();
	}
	else if (currentGameState == GameState::won) {
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
	//Close window on "Esc" key
	//if (key == 27) {	// escape
	//	glutDestroyWindow(window);
	//	exit(0);
	//}
	
	glutPostRedisplay();
}

void keyboardSpecial(int key, int x, int y) {
	if(currentGameState==GameState::playing) {
		if(key==GLUT_KEY_DOWN){		//only handly clicks, not releases
			if(game.getSelectedVehicle()->moveDown()){	//if the vehicle can move, move it
				game.getMetrics().increaseMoveCount();	//& increase the number of moves used
			}
		}
		else if(key==GLUT_KEY_LEFT){
			if(game.getSelectedVehicle()->moveLeft()){
				game.getMetrics().increaseMoveCount();
			}
		}
		else if(key==GLUT_KEY_RIGHT){
			if(!game.getSelectedVehicle()->isInWinningSpace()){		//only move if the game isn't over. Special Vehicle could have won the game by moving right
				if(game.getSelectedVehicle()->moveRight()){
					game.getMetrics().increaseMoveCount();
				}
			}
			//Check if that move won the game
			if(game.getSelectedVehicle()->isInWinningSpace()){
				currentGameState = GameState::won;
			}
		}
		else if(key==GLUT_KEY_UP){
			if(game.getSelectedVehicle()->moveUp()){
				game.getMetrics().increaseMoveCount();
			}
		}
	}
	glutPostRedisplay();
}

void cursor(int x, int y) {
	mouseXPosition = x;		//update global mouse position variables
	mouseYPosition = y;

	if(currentGameState == GameState::playing){
		//Loop over all vehicles & check if the cursor overlaps with any of them
		for(int i=0; i<game.getVehicles().size(); i++){
			if(i != game.getSelectedVehicleIndex()) {	//Skip checking the currently selected vehicle since it's already been lightened
				if(game.getVehicles()[i]->isOverlapping(x, y)){
					Color initialColor = game.getVehicles()[i]->getInitialColor();		//save temporary color, for readability. Could be 1 line
					game.getVehicles()[i]->setColor(lightenColor(initialColor, HOVER_PERCENT_CHANGE));
				}
				else{		//else set back to its initial color if NOT overlapping
					game.getVehicles()[i]->setColor( game.getVehicles()[i]->getInitialColor() );
				}
			}
		}
	}

	if(game.getSaveButton().isOverlapping(x, y)){
		Color initialColor = game.getSaveButton().getInitialColor();
		game.getSaveButton().setColor(lightenColor(initialColor, HOVER_PERCENT_CHANGE));
	}
	else{
		game.getSaveButton().setColor(game.getSaveButton().getInitialColor());
	}

	if(game.getLoadButton().isOverlapping(x, y)){
		Color initialColor = game.getLoadButton().getInitialColor();
		game.getLoadButton().setColor(lightenColor(initialColor, HOVER_PERCENT_CHANGE));
	}
	else{
		game.getLoadButton().setColor(game.getLoadButton().getInitialColor());
	}

	if(game.getRestartButton().isOverlapping(x, y)){
		Color initialColor = game.getRestartButton().getInitialColor();
		game.getRestartButton().setColor(lightenColor(initialColor, HOVER_PERCENT_CHANGE));
	}
	else{
		game.getRestartButton().setColor(game.getRestartButton().getInitialColor());
	}

	if(game.getNewGameButton().isOverlapping(x, y)){
		Color initialColor = game.getNewGameButton().getInitialColor();
		game.getNewGameButton().setColor(lightenColor(initialColor, HOVER_PERCENT_CHANGE));
	}
	else{
		game.getNewGameButton().setColor(game.getNewGameButton().getInitialColor());
	}
	glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
	if(state==GLUT_DOWN){	//only register clicks, not releases
		if(currentGameState == GameState::playing){
			//Loop over vehicles to see if mouse actually clicked any of them
			for(int i=0; i<game.getVehicles().size(); i++){
				if(game.getVehicles()[i]->isOverlapping(x, y)){		//if point is inside the vehicle boundary
					game.setSelectedVehicleIndex(i);		//we found a vehicle that was clicked, so update to be the vehicle to be moved
					Color initialColor = game.getVehicles()[i]->getInitialColor();
					game.getVehicles()[i]->setColor(lightenColor(initialColor, HOVER_CLICK_PERCENT_CHANGE));	//brighten the color even more than hover
				}
			}

			//Buttons that only work during gameplay
			if(game.getSaveButton().isOverlapping(x, y)){
				game.save();
				game.setStatusMessage("Game Saved");
			}
		}

		//Handle buttons that always work
		if(game.getLoadButton().isOverlapping(x, y)){
			game.setStatusMessage("Loaded previous game");
			game.load();
			currentGameState=GameState::playing;	//update game state incase they clicked after winning a game
		}
		else if(game.getNewGameButton().isOverlapping(x, y)){
			game.newGame();
			game.setStatusMessage("New Game");
			currentGameState=GameState::playing;	//update game state incase they clicked after winning a game
		}
		else if(game.getRestartButton().isOverlapping(x, y)){
			game.restart();
			game.setStatusMessage("Restart");
			currentGameState=GameState::playing;	//update game state incase they clicked after winning a game
		}
	}
	glutPostRedisplay();
}

void drag(int x, int y){
}

void timer(int extra) {
	if(currentGameState == GameState::playing){
		//Lighten if color is less than 255, darken if < the initial color
		if(game.getSelectedVehicle()->shouldLighten()){
			int lightenIncrease = 1;	//positive to lighten
			game.getSelectedVehicle()->setColor(lightenColor(game.getSelectedVehicle()->getColor(), lightenIncrease));
			if(game.getSelectedVehicle()->isColorMaxed()){	//change to darken if it's maxed
				game.getSelectedVehicle()->setDarken();
			}
		}
		else{
			int lightenIncrease = -1;	//negative to darken
			game.getSelectedVehicle()->setColor(lightenColor(game.getSelectedVehicle()->getColor(), lightenIncrease));
			if(game.getSelectedVehicle()->isColorInitial()){	//change to lighten if it is the initial color
				game.getSelectedVehicle()->setLighten();
			}
		}
	}

	glutTimerFunc(10, timer, 0);
	glutPostRedisplay();
}

void runGame(int argc, char** argv){
	init();
	
	glutInit(&argc, argv);		// Initialize GLUT
	
	glutInitDisplayMode(GLUT_RGBA);		//allow transparency
	
	glutInitWindowSize((int)windowWidth, (int)windowHeight);
	glutInitWindowPosition(100, 100);	// Position the window's initial top-left corner

	window = glutCreateWindow("Rush Hour");		// create the window and store the handle to it

	glutDisplayFunc(display);	// Register callback handler for window re-paint event

	initGL();	// Our own OpenGL initialization
	
	glutKeyboardFunc(keyboard);	// register keyboard press event processing function works for numbers, letters, spacebar, etc.
	
	glutSpecialFunc(keyboardSpecial);	// register special event: function keys, arrows, etc.
	
	glutPassiveMotionFunc(cursor);	// handles mouse movement
	
	glutMouseFunc(mouse);	// handles mouse click
	
	glutTimerFunc(0, timer, 0);	// handles timer
	
	glutMainLoop();	// Enter the event-processing loop
}


//Main function: GLUT runs as a console application starting at main()
int main(int argc, char** argv) {
	// cout << "Enter 1 to play, 0 to test: ";
	int choice;
	// cin >> choice;
	choice = 1;	//Hack for playing mode
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