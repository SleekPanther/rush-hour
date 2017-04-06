#ifndef ScoreMetrics_hpp
#define ScoreMetrics_hpp

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ScoreMetrics {
private:
	static const int moveMultiplier;		//how much each move is costs the player
	int moveCount;		//how many moves

public:
	ScoreMetrics();
	~ScoreMetrics();
};

#endif