//
//  ScoreMetrics.cpp
//  CS 120
//
//  Created by xiaosong chen on 4/13/17.
//  Copyright © 2017 Xiaosong Chen. All rights reserved.
//

#include "ScoreMetrics.hpp"

ScoreMetrics::ScoreMetrics(): moveCount(0) {
}

ScoreMetrics::~ScoreMetrics() {
}

int ScoreMetrics::getMoveCount() const{
	return moveCount;
}

void ScoreMetrics::increaseMoveCount(){
	moveCount = moveCount +1;
}

void ScoreMetrics::reset() {
	moveCount = 0;
}