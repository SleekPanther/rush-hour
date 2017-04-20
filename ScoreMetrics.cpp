#include "ScoreMetrics.h"

ScoreMetrics::ScoreMetrics(): moveCount(0) {
}

ScoreMetrics::~ScoreMetrics() {
}

int ScoreMetrics::getMoveCount() const{
	return moveCount;
}

void ScoreMetrics::setMoveCount(int previousMoves){
	moveCount = previousMoves;
}

void ScoreMetrics::increaseMoveCount(){
	moveCount = moveCount +1;
}

void ScoreMetrics::reset() {
	moveCount = 0;
}