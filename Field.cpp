#include "include/Field.h"

// Empty constructor
Field::Field() {}

int Field::GetHeight()
{
    return FIELD_HEIGHT;
}

int Field::GetWidth()
{
    return FIELD_WIDTH;
}

int Field::GetRightEdgeXVal()
{
    return X_MAX;
}

int (*Field::GetField())[10] 
{
    return field;
}

void Field::FieldLandingHandler(int piece_type, int* x, int* y)
{
    // Merge the landed piece into the rest of the field!
    for (int i = 0; i < 4; i++) field[y[i]][x[i]] = piece_type + 1;
}

int Field::DetectFullRow()
{
    for (int i = 0; i < FIELD_HEIGHT; i++)
    {
        int count = 0;
        for (int j = 0; j < FIELD_WIDTH; j++) if (field[i][j] != 0) count++; else break;
        if (count == 10) return i;
    }
    return -1;
}

int Field::DeleteFullRows()
{
    int num_full_rows = 0;
    int row = DetectFullRow();
    while (row != -1)
    {
        for (int i = row; i > 0; i--)
            for (int j = 0; j < FIELD_WIDTH; j++)
            {
                field[i][j] = field[i-1][j];
                field[i-1][j] = 0;
            }
        num_full_rows++;
        row = DetectFullRow();
    }
    return num_full_rows;
}

bool Field::TopRowFilled()
{
    for (int i = 0; i < FIELD_WIDTH; i++) if (field[0][i] != 0) return true;
    return false;
}