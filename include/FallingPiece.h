#ifndef FALLINGPIECE_H
#define FALLINGPIECE_H

#include <string>
#include <time.h>
#include <SFML/Graphics.hpp>
using namespace sf;
using std::string;

class FallingPiece
{
    public:
        FallingPiece();
        int GetNumFigs();
        void DropNewPiece();
        bool UserEventHandler(Event* e);
        void RotatePiece(int (*field)[10], int X_MAX);
        void CheckBottomCollision(int (*field)[10]);
        void MoveDown();
        void CheckHorizontalCollision(int (*field)[10], int X_MAX);
        void MoveLeftOrRight();
        void PieceLandingHandler();
        void SetLandingFlag();
        void ResetSettings();
        int GetCurrentPieceType();
        int *GetX();
        int *GetY();
        bool PieceIsLanded();
        bool PieceIsLandedDelayed();
        int Getdx();

    private:
        const int INIT_X_OFFSET = 4;
        const int INIT_Y_OFFSET = -6;
        const int NUM_FIGS = 7;
        const int TILES = 4;
        const int figures[7][4] = 
        {
            1,3,5,7,
            2,4,5,7,
            3,5,4,6,
            3,5,4,7,
            2,3,5,7,
            3,5,7,6,
            2,3,4,5
        };
        int x[4];
        int y[4];
        int temp_x[4];
        int temp_y[4];
        int dx = 0;
        int dy = 1;
        int shift1 = 0;
        int counter = 0;
        int curr_piece_type;
        int field_shift_dir = 0;
        bool DROP_FLAG = true;
        bool ROTATE = false;
        bool FIELD_COL_FLAG = true;
        bool LANDED = false;
        bool LANDED_DELAYED = false;
};

#endif