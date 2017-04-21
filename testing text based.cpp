#include "textTestingFunctions.h"
//#include <GL/glut.h>

int main() {
	cout << boolalpha;
	cout << "Testing Starts (in main)" << endl;
	runAllTests();

	cout << "\n\nUser testing load/save\n";
	chooseLoadSave();

	return 0;
}