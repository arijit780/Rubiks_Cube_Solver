#include "RubiksCube.h"

/*
    (FACE,row,col) for 3D representation of RubiksCube-------------------------------------------------------------------

                                (0,0,0) (0,0,1) (0,0,2)
                                (0,1,0) (0,1,1) (0,1,2)
                                (0,2,0) (0,2,1) (0,2,2)

    (1,0,0) (1,0,1) (1,0,2)     (2,0,0) (2,1,0) (2,1,1)     (3,0,0) (3,0,1) (3,0,2)     (4,0,0) (4,0,1) (4,0,2)
    (1,1,0) (1,1,1) (1,1,2)     (2,1,0) (2,1,1) (2,1,2)     (3,1,0) (3,1,1) (3,1,2)     (4,1,0) (4,1,1) (4,1,2) 
    (1,2,0) (1,2,1) (1,2,2)     (2,2,0) (2,2,1) (2,2,2)     (3,2,0) (3,2,1) (3,2,2)     (4,2,0) (4,2,1) (4,2,2) 

                                (5,0,0) (5,0,1) (5,0,2)
                                (5,1,0) (5,1,1) (5,1,2)
                                (5,2,0) (5,2,1) (5,2,2)

*/

class RubiksCube3dArray : public RubiksCube {
private:

    void rotateFace(int ind){
        char temp[3][3] = {};
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                temp[i][j] = cube[ind][i][j];
            }
        }
        for(int i = 0; i < 3; i++) cube[ind][0][i] = temp[2-i][0];
        for(int i = 0; i < 3; i++) cube[ind][i][2] = temp[0][i];
        for(int i = 0; i < 3; i++) cube[ind][2][i] = temp[2-i][2];
        for(int i = 0; i < 3; i++) cube[ind][i][0] = temp[2][i];
    }

public:
    char cube[6][3][3]{};

//  Constructor
    RubiksCube3dArray() {
        for(int i = 0; i < 6; i++) {
            for(int j = 0; j < 3; j++) {
                for(int k = 0; k < 3; k++) {
                    cube[i][j][k] = getColorLetter(COLOR(i));
                }
            }
        }
    }

    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        char color = cube[int(face)][row][col];
        switch(color) {
            case 'R':
                return COLOR::RED;
            case 'G':
                return COLOR::GREEN;
            case 'B':
                return COLOR::BLUE;
            case 'Y':
                return COLOR::YELLOW;
            case 'O':
                return COLOR::ORANGE;
            default:
                return COLOR::WHITE;
        }
    }

    bool isSolved() const override { 
        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 3; j++){
                for(int k = 0; k < 3; k++){
                    if (this->cube[i][j][k] == getColorLetter(COLOR(i))) continue;
                    return false;
                }
            }
        }
        return true;
    }

 // rotation logic goes here
    RubiksCube &u() override {
        this->rotateFace(0);

        char temp[3] = {};
        for(int i = 0; i < 3; i++) temp[i] = cube[1][0][i];
        for(int i = 0; i < 3; i++) cube[1][0][i] = cube[2][0][i];
        for(int i = 0; i < 3; i++) cube[2][0][i] = cube[3][0][i];
        for(int i = 0; i < 3; i++) cube[3][0][i] = cube[4][0][i];
        for(int i = 0; i < 3; i++) cube[4][0][i] = temp[i];

        return *this;
    }

    RubiksCube &u2() override {
        this->u();
        this->u();

        return *this;
    }

    RubiksCube &uPrime() override {
        this->u();
        this->u();
        this->u();

        return *this;
    }

    RubiksCube &l() override {
        this->rotateFace(1);
        
        char temp[3] = {};
        for(int i = 0; i < 3; i++) temp[i] = cube[0][i][0];
        for(int i = 0; i < 3; i++) cube[0][i][0] = cube[4][2-i][2];
        for(int i = 0; i < 3; i++) cube[4][2-i][2] = cube[5][i][0];
        for(int i = 0; i < 3; i++) cube[5][i][0] = cube[2][i][0];
        for(int i = 0; i < 3; i++) cube[2][i][0] = temp[i];

        return *this;
    }

    RubiksCube &l2() override {
        this->l();
        this->l();

        return *this;
    }

    RubiksCube &lPrime() override {
        this->l();
        this->l();
        this->l();

        return *this;
    }

    RubiksCube &f() override {
        this->rotateFace(2);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0][2][i];
        for (int i = 0; i < 3; i++) cube[0][2][i] = cube[1][2 - i][2];
        for (int i = 0; i < 3; i++) cube[1][2 - i][2] = cube[5][0][2 - i];
        for (int i = 0; i < 3; i++) cube[5][0][2 - i] = cube[3][i][0];
        for (int i = 0; i < 3; i++) cube[3][i][0] = temp_arr[i];

        return *this;
    }

    RubiksCube &f2() override {
        this->f();
        this->f();

        return *this;
    }

    RubiksCube &fPrime() override {
        this->f();
        this->f();
        this->f();

        return *this;
    }

    RubiksCube &r() override {
        this->rotateFace(3);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0][2 - i][2];
        for (int i = 0; i < 3; i++) cube[0][2 - i][2] = cube[2][2 - i][2];
        for (int i = 0; i < 3; i++) cube[2][2 - i][2] = cube[5][2 - i][2];
        for (int i = 0; i < 3; i++) cube[5][2 - i][2] = cube[4][i][0];
        for (int i = 0; i < 3; i++) cube[4][i][0] = temp_arr[i];

        return *this;
    }

    RubiksCube &r2() override {
        this->r();
        this->r();

        return *this;
    }

    RubiksCube &rPrime() override {
        this->r();
        this->r();
        this->r();

        return *this;
    }

    RubiksCube &b() override {
        this->rotateFace(4);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0][0][2 - i];
        for (int i = 0; i < 3; i++) cube[0][0][2 - i] = cube[3][2 - i][2];
        for (int i = 0; i < 3; i++) cube[3][2 - i][2] = cube[5][2][i];
        for (int i = 0; i < 3; i++) cube[5][2][i] = cube[1][i][0];
        for (int i = 0; i < 3; i++) cube[1][i][0] = temp_arr[i];

        return *this;
    }

    RubiksCube &b2() override {
        this->b();
        this->b();

        return *this;
    }

    RubiksCube &bPrime() override {
        this->b();
        this->b();
        this->b();

        return *this;
    }

    RubiksCube &d() override {
        this->rotateFace(5);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[2][2][i];
        for (int i = 0; i < 3; i++) cube[2][2][i] = cube[1][2][i];
        for (int i = 0; i < 3; i++) cube[1][2][i] = cube[4][2][i];
        for (int i = 0; i < 3; i++) cube[4][2][i] = cube[3][2][i];
        for (int i = 0; i < 3; i++) cube[3][2][i] = temp_arr[i];

        return *this;
    }

    RubiksCube &d2() override {
        this->d();
        this->d();

        return *this;
    }

    RubiksCube &dPrime() override {
        this->d();
        this->d();
        this->d();

        return *this;
    }

 // operator overloading
    bool operator==(const RubiksCube3dArray &r1) const {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (r1.cube[i][j][k] != cube[i][j][k]) return false;
                }
            }
        }
        return true;
    }

    RubiksCube3dArray &operator=(const RubiksCube3dArray &r1) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    cube[i][j][k] = r1.cube[i][j][k];
                }
            }
        }
        return *this;
    }
};

struct Hash3d {
    size_t operator()(const RubiksCube3dArray &r1) const {
        string str = "";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    str += r1.cube[i][j][k];
                }
            }
        }
        return hash<string>()(str);
    }

};