#include "GameSetup.h"

GameSetup::GameSetup() {
	setups = {
			{1, 1, 2, 4, 2, 3, 2, 2, 2, 4, 3, 4, 2, 1, 0, 1, 1}, 
			{1, 1, 2, 2, 2, 3, 2, 3, 3, 5, 4, 5, 5, 5, 3, 5, 2, 5, 3, 5, 4}, 
			{3, 4, 2, 1, 2, 2, 2, 2, 0, 0, 1, 0, 2, 4, 4, 5, 4, 3, 2, 5, 3, 5, 4, 5, 3, 0, 1, 0, 2, 0, 3, 2, 0, 4, 0, 5, 3, 5, 0, 5, 1, 5, 2, 3, 3, 1, 3, 2, 3, 3}, 
			{2, 3, 2, 1, 2, 2, 2, 2, 1, 3, 2, 3, 2, 2, 5, 3, 5, 2, 1, 4, 1, 5, 3, 3, 2, 3, 3, 3, 4, 3, 5, 3, 5, 4, 5, 5}, 
			{4, 6, 2, 0, 2, 1, 2, 2, 2, 0, 3, 0, 2, 4, 0, 5, 0, 2, 4, 1, 5, 1, 3, 1, 3, 2, 3, 3, 3, 2, 1, 0, 1, 1, 3, 0, 3, 0, 4, 0, 5, 2, 2, 4, 2, 5, 3, 4, 2, 4, 3, 4, 4, 2, 5, 2, 5, 3, 2, 5, 4, 5, 5}, 
			{7, 4, 2, 1, 2, 2, 2, 2, 0, 0, 1, 0, 2, 0, 1, 1, 1, 3, 1, 3, 2, 3, 3, 3, 2, 0, 5, 1, 5, 2, 4, 4, 5, 4, 2, 4, 5, 5, 5, 2, 4, 0, 5, 0, 2, 2, 0, 2, 1, 3, 0, 2, 0, 3, 0, 4, 2, 3, 4, 3, 5, 3, 5, 1, 5, 2, 5, 3}, 
			{6, 5, 2, 0, 2, 1, 2, 3, 1, 0, 2, 0, 3, 0, 2, 2, 1, 3, 1, 2, 4, 1, 5, 1, 2, 0, 3, 1, 3, 3, 0, 4, 1, 4, 2, 4, 3, 0, 5, 1, 5, 2, 5, 2, 0, 0, 0, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 3, 5, 2, 4, 4, 4, 5, 2, 5, 4, 5, 5}, 
			{3, 4, 2, 1, 2, 2, 2, 2, 0, 0, 1, 0, 2, 4, 4, 5, 4, 3, 2, 5, 3, 5, 4, 5, 3, 0, 1, 0, 2, 0, 3, 2, 0, 4, 0, 5, 3, 3, 1, 3, 2, 3, 3, 3, 5, 0, 5, 1, 5, 2}, 
			{2, 3, 2, 1, 2, 2, 2, 2, 1, 3, 2, 3, 2, 2, 5, 3, 5, 3, 3, 2, 3, 3, 3, 4, 2, 1, 4, 1, 5, 3, 5, 3, 5, 4, 5, 5}
	};
}

GameSetup::GameSetup(int setupNumber): GameSetup() {
	//Old code that enables reading from files
	// string setupFilename = setupBaseFilename + to_string(setupNumber) + setupExtension;
	// ifstream testFile(setupFilename);		//attempt to open the file & see if it exists
	// if(!testFile){
	// 	setupFilename = defaultSetupFilename;
	// }
	// vehicleLocations = GameSetup::readFile(setupFilename);

	setupNumber = setupNumber -1;	//adjust for vector indexes
	cout << setupNumber << "\n";
	vehicleLocations = setups[setupNumber];
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