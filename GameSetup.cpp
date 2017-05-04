#include "GameSetup.h"

GameSetup::GameSetup() {
}

GameSetup::GameSetup(int setupNumber) {
	string setupFilename = setupBaseFilename + to_string(setupNumber) + setupExtension;
	ifstream testFile(setupFilename);		//attempt to open the file & see if it exists
	if(!testFile){
		setupFilename = defaultSetupFilename;
	}
	vehicleLocations = GameSetup::readFile(setupFilename);
}

GameSetup::~GameSetup() {
}

int GameSetup::getRandomInt(int lowerBound, int upperBound){
	if(lowerBound>upperBound){	//reverse parameters if passed in backwards
		int temp = lowerBound;
		lowerBound = upperBound;
		upperBound = temp;
	}
	random_device randomGenerator;
	int range = upperBound - lowerBound +1;		//+1 to make upperBound inclusive
	return randomGenerator() % range  + lowerBound;
}

vector<int> GameSetup::getSetupAsList() const{
	return vehicleLocations;
}

vector<int> GameSetup::readFile(string filename){
	vector<int> fileContents;

	ifstream inputFile(filename);
	if(inputFile){
		int number;
		while(inputFile >> number){			//go to the end of file. (This only contains integers so it should be OK)
			fileContents.push_back(number);
		}
	}
	inputFile.close();
	return fileContents;
}

void GameSetup::printVector(vector<int> vector){
	for(int i=0; i<vector.size(); i++){
		cout << vector[i] << ", ";
	}
	cout << '\n';
}