#include "include/FallingPiece.h"


// Empty constructor
FallingPiece::FallingPiece() 
{
    // Random number generator seed
    srand(time(NULL));
}

int FallingPiece::GetNumFigs()
{
    return NUM_FIGS;
}

void FallingPiece::DropNewPiece()
{
    if (DROP_FLAG)
    {
        DROP_FLAG = false;
        curr_piece_type = rand() % NUM_FIGS;
        for (int i = 0; i < TILES; i++) 
        {
            x[i] = (figures[curr_piece_type][i] % 2) + INIT_X_OFFSET;
            y[i] = (figures[curr_piece_type][i] / 2) + INIT_Y_OFFSET;
        }
    }
}

bool FallingPiece::UserEventHandler(Event* e)
{
    if ((*e).type == Event::Closed) return true;

    if ((*e).type == Event::KeyPressed) 
    {
        if ((*e).key.code == Keyboard::Up) ROTATE = true;
        else if ((*e).key.code == Keyboard::Left) dx = -1;
        else if ((*e).key.code == Keyboard::Right) dx = 1;
        else if ((*e).key.code == Keyboard::Down) MoveDown();
    }
    return false;
}

void FallingPiece::RotatePiece(int (*field)[10], int X_MAX)
{
    if (ROTATE && !PieceIsLanded())
    {
        ROTATE = false;
        // Just in case rotation is impossible, save the current position.
        for (int i = 0; i < TILES; i++) 
        {
            temp_x[i] = x[i];
            temp_y[i] = y[i];
        }

        // Use (x[1], y[1]) as the center of rotation point
        for (int i = 0; i < TILES; i++) 
        {
            // Perform rotation (difference in y position will be the diff in x position).
            int x_difference = y[i] - y[1];
            int y_difference = x[i] - x[1];
            x[i] = x[1] - x_difference;
            y[i] = y[1] + y_difference;

            // Check if our rotation will go out of the frame. 
            // If so, compensate via shifting.
            if (x[i] < 0 && x[i] < shift1) // Left side of frame.
                shift1 = x[i]; 
            else if (x[i] > X_MAX && x[i] - X_MAX > shift1) // Right side of frame.
                shift1 = x[i] - X_MAX;
        }

        // Shift compensation.
        for (int i = 0; i < TILES; i++) x[i] -= shift1;

        // Check if our rotation will collide with the field. If so, compensate as well.
        // Assume collision to start.
        while (FIELD_COL_FLAG)
        {
            FIELD_COL_FLAG = false;

            counter += 1;
            if (counter == 12) 
            {
                for (int i = 0; i < TILES; i++) 
                {
                    x[i] = temp_x[i];
                    y[i] = temp_y[i];
                } 
                break;
            }

            for (int i = 0; i < TILES; i++)
            {
                int curr_x = x[i];
                int curr_y = y[i];

                // Case that field collision occurs.
                if ((*(field + curr_y))[curr_x] != 0)
                {
                    FIELD_COL_FLAG = true;

                    for (int j = 0; j < TILES; j++)
                    {
                        if (x[j] == curr_x && y[j] == curr_y - 1) {field_shift_dir = 1; break;}
                        else if (x[j] == curr_x + 1 && y[j] == curr_y) {field_shift_dir = 2; break;}
                        else if (x[j] == curr_x - 1 && y[j] == curr_y) {field_shift_dir = 3; break;}
                    }
                }
            }

            // Perform compensation.
            switch (field_shift_dir)
            {
                case 1: for (int i = 0; i < TILES; i++) y[i] -= 1; break;
                case 2: for (int i = 0; i < TILES; i++) x[i] -= 1; break;
                case 3: for (int i = 0; i < TILES; i++) x[i] += 1; break;
                default: break;
            }
        }
    }
}

void FallingPiece::CheckBottomCollision(int (*field)[10]) 
{
    for (int i = 0; i < TILES; i++) 
    {
        if (y[i] >= -1 && y[i] <= 18)
        {
            if ((*(field + y[i] + 1))[x[i]] != 0) 
            {
                LANDED = true; 
                break;
            }
        }
        else if (y[i] > 18) 
        {
            LANDED = true;
            break;
        }
    }
}

void FallingPiece::SetLandingFlag()
{
    LANDED_DELAYED = LANDED;
}

void FallingPiece::MoveDown()
{
    if (!PieceIsLanded()) for (int i = 0; i < TILES; i++) y[i] += dy;
}

void FallingPiece::CheckHorizontalCollision(int (*field)[10], int X_MAX) 
{
    for (int i = 0; i < TILES; i++) 
    {
        // Field collision.
        if (((*(field + y[i]))[x[i]-1] != 0 && dx == -1) || ((*(field + y[i]))[x[i]+1] != 0 && dx == 1)) 
            dx = 0;
        // Frame collision (cannot go out of bounds).
        if ((x[i] == 0 && dx == -1) || (x[i] == X_MAX && dx == 1)) 
            dx = 0; 
    } 
}

void FallingPiece::MoveLeftOrRight()
{
    for (int i = 0; i < TILES; i++) x[i] += dx;
}

bool FallingPiece::PieceIsLanded()
{
    return LANDED;
}

bool FallingPiece::PieceIsLandedDelayed()
{
    return LANDED_DELAYED;
}

void FallingPiece::PieceLandingHandler()
{
    LANDED = false;
    LANDED_DELAYED = false;
    DROP_FLAG = true;
}

void FallingPiece::ResetSettings()
{
    dx = 0;
    shift1 = 0;
    field_shift_dir = 0;
    counter = 0;
    FIELD_COL_FLAG = true;
}

int FallingPiece::GetCurrentPieceType()
{
    return curr_piece_type;
}

int* FallingPiece::GetX()
{
    return &x[0];
}

int* FallingPiece::GetY()
{
    return &y[0];
}

int FallingPiece::Getdx()
{
    return dx;
}