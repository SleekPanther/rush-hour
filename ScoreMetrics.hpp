//
//  ScoreMetrics.hpp
//  CS 120
//
//  Created by xiaosong chen on 4/13/17.
//  Copyright © 2017 Xiaosong Chen. All rights reserved.
//

#ifndef ScoreMetrics_hpp
#define ScoreMetrics_hpp

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ScoreMetrics {
private:
	int moveCount;		//how many moves

public:
	ScoreMetrics();
	~ScoreMetrics();

	int getMoveCount() const;

	// Requires: nothing
	// Modifies: moveCount
	// Effects: Adds 1 to moveCount
	void increaseMoveCount();

	// Requires: nothing
	// Modifies: moveCount
	// Effects: resets moveCount to 0 when starting new game
	void reset();
};

#endif
