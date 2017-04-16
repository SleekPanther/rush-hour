#ifndef ScoreMetrics_hpp
#define ScoreMetrics_hpp

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ScoreMetrics {
private:
    int moveCount;	
    
public:
    ScoreMetrics();
    ~ScoreMetrics();
    void increaseMoveCount();
    void reset();
    int getMoveCount();
    
};

#endif
