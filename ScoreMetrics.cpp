//
//  ScoreMetrics.cpp
//  CS 120
//
//  Created by xiaosong chen on 4/13/17.
//  Copyright © 2017 Xiaosong Chen. All rights reserved.
//

#include "ScoreMetrics.hpp"

ScoreMetrics::ScoreMetrics() {
    cout << "\t new score metrics " << endl;
}

ScoreMetrics::~ScoreMetrics() {
}

void ScoreMetrics::increaseMoveCount(){
    moveCount = moveCount +1;
}


void ScoreMetrics::reset() {
    moveCount = 0;
    cout << "\t Game Reset" << endl;
}


int ScoreMetrics::getMoveCount(){
    return moveCount;
}

