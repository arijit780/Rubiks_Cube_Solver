#include <bits/stdc++.h>
#include "Model/RubiksCube.cpp"
// #include "Model/RubiksCube3dArray.cpp"
// #include "Model/RubiksCube1dArray.cpp"
#include "Model/RubiksCubeBitboard.cpp"
// #include "Solver/DFSSolver.h"
// #include "Solver/BFSSolver.h"
// #include "Solver/IDDFSSolver.h"
// #include "Solver/IDAstarSolver_v0.h"
#include "Solver/IDAstarSolver.h"
#include "PatternDatabases/CornerPatternDatabase.h"
#include "PatternDatabases/CornerPatternDatabase.cpp"
#include "PatternDatabases/PatternDatabase.h"
#include "PatternDatabases/PatternDatabase.cpp"
#include "PatternDatabases/CornerDBMaker.h"
#include "PatternDatabases/CornerDBMaker.cpp"
#include "PatternDatabases/NibbleArray.h"
#include "PatternDatabases/NibbleArray.cpp"
#include "PatternDatabases/math.h"
#include "PatternDatabases/math.cpp"
#include "PatternDatabases/PermutationIndexer.h"

using namespace std;

/*
    All the testing of the functions and algorithms is in the test.cpp file
    Here, we have the best version available i.e., "Bitboard representation" as cube model and "IDAstarSolver" as Solver
    We can create the "Corner Pattern Database" based on different depth by varying the second parameter of the "CornerDBMaker dbMaker(filename, variable_depth)"
    Testing the code for different databases and number of shuffles is done here
    I have also implemented an interactive shuffle so that we can shuffle the cube as we want and then see it solve for different databases 

    To generate an interactive shuffle, input the number based on following instructions and press 0 to exit:
    0: EXIT and Solve the Rubiks Cube
    1: L                2: L'               3: L2               4: R                5: R'               6: R2
    7: U                8: U'               9: U2               10: D               11: D'              12: D2
    13: F               14: F'              15: F2              16: B               17: B'              18: B2
*/

int main(){
    string fileName = "E:\\CPP Projects\\Rubiks Cube Solver\\Rubiks Cube Solver\\Databases\\cornerDepth.txt";

    // CornerDBMaker dbMaker(fileName, 8);
    // dbMaker.bfsAndStore();

    // Uncomment for interactive shuffle:
    
    // RubiksCubeBitboard cube;
    // vector<string> shuffleMoves;
    // while(1){
    //     int x;
    //     cin>>x;
    //     if(x==0) break;
    //     if(x<0 || x>18) { cout<<"Invalid"<<endl; return 0;}
    //     shuffleMoves.push_back(cube.getMove(RubiksCube::MOVE(x-1)));
    //     switch(x){
    //         case 1: cube.l(); break;
    //         case 2: cube.lPrime(); break;
    //         case 3: cube.l2(); break;
    //         case 4: cube.r(); break;
    //         case 5: cube.rPrime(); break;
    //         case 6: cube.r2(); break;
    //         case 7: cube.u(); break;
    //         case 8: cube.uPrime(); break;
    //         case 9: cube.u2(); break;
    //         case 10: cube.d(); break;
    //         case 11: cube.dPrime(); break;
    //         case 12: cube.d2(); break;
    //         case 13: cube.f(); break;
    //         case 14: cube.fPrime(); break;
    //         case 15: cube.f2(); break;
    //         case 16: cube.b(); break;
    //         case 17: cube.bPrime(); break;
    //         case 18: cube.b2(); break;
    //     }
    // }
    // // cout<<"\nMoves Peformed:\n";
    // cube.print();
    // for(auto it: shuffleMoves) cout<<it<<" ";
    // cout<<endl;

    // Uncomment for Randomshuffle
    RubiksCubeBitboard cube;
    auto shuffleMoves = cube.randomShuffleCube(6);
    cube.print();
    for (auto move: shuffleMoves) cout << cube.getMove(move) << " ";
    cout << "\n";


    IDAstarSolver<RubiksCubeBitboard, HashBitboard> idaStarSolver(cube, fileName);
    auto moves = idaStarSolver.solve();

    idaStarSolver.rubiksCube.print();
    for (auto move: moves) cout << cube.getMove(move) << " ";
    cout << "\n";

    return 0;
}