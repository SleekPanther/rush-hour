#ifndef ScoreMetrics_h
#define ScoreMetrics_h

#include <iostream>
#include <string>

using namespace std;

class ScoreMetrics {
private:
	int moveCount;

public:
	ScoreMetrics();
	~ScoreMetrics();

	int getMoveCount() const;

	// Requires: nothing
	// Modifies: moveCount
	// Effects: used when continuing an old game to set the moveCount equal to an input parameter
	void setMoveCount(int previousMoves);

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