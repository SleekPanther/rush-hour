#include "textTestingFunctions.h"
//#include <GL/glut.h>

int main() {
	cout << boolalpha;
	runAllTests();

	cout << "\n\nUser testing load/save\n";
	chooseLoadSave();

	return 0;
}