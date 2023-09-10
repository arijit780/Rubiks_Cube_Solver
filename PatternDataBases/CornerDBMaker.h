#include "CornerPatternDatabase.h"
// #include "../Model/RubiksCubeBitboard.cpp"

using namespace std;

#ifndef RUBIKS_CUBE_SOLVER_CORNERDBMAKER_H
#define RUBIKS_CUBE_SOLVER_CORNERDBMAKER_H

class CornerDBMaker {
private:
    string fileName;
    CornerPatternDatabase cornerDB;

public:
    CornerDBMaker(string _fileName);
    CornerDBMaker(string _fileName, uint8_t init_val);

    bool bfsAndStore();
};


#endif //RUBIKS_CUBE_SOLVER_CORNERDBMAKER_H
