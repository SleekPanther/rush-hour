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
    void increaseMoveCount();
    void reset();
    int getMoveCount();
    
};

#endif
